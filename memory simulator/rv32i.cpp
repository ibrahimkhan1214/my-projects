//-------------------------------------------------------------
//rv32i.cpp
//CSCI 463 Assignment 5
//
//created by Ibrahim Khan (z1837663)
//
//--------------------------------------------------------------

#include "hex.h"
#include "memory.h"
#include "rv32i.h"
#include "registerfile.h"
#include<cstdlib>
#include<iostream>
#include<iomanip>
#include<bitset>
#include<sstream>

using std::string;
using std::cout;
using std::endl;

rv32i::rv32i(memory *m)
{
	mem = m;		//saving m argument in the mem(pointer to the memory object)
}

/*
Decode method will decode the instruction(insn) passed in.
This method will Not print anything but return a string only containing formated addresses.
*/

string rv32i::decode(uint32_t insn) const
{

	std::ostringstream os;
	os << hex32(insn)<<"   ";	//memory addresses

	/*
	// This switch statement will decode following instructions
	// ->lui   ->auipc   ->jal   ->jalr   ->beq   ->bne   ->blt
	// ->bge   ->bltu    ->bgeu  ->lb     ->lh    ->lbu   ->lhu
        // ->sb    ->sh      ->jal   ->sw     ->addi  ->slti  ->sltiu
        // ->xori  ->ori     ->andi  ->slli   ->srli  ->srai  ->add
        // ->sub   ->sll     ->slt   ->sltu   ->xor   ->srl   ->sra
        // ->or    ->and
        // Special cases: fence, ecall, ebreak.
	*/

	switch(get_opcode(insn))
	{
	case 0b0110111:	// U-type instruction
		os << "lui    x" << std::dec << get_rd(insn) << ",0x" << std::hex << ((get_imm_u(insn) >> 12)&0x0fffff);
		break;
	case 0b0010111: // U-type instruction
		 os << "auipc  x" << std::dec << get_rd(insn) << ",0x" << std::hex << ((get_imm_u(insn) >> 12)&0x0fffff);
                break;
	case 0b1101111: // J-type instruction
		 os << "jal    x" << std::dec << get_rd(insn) << ",0x" << std::hex << get_imm_j(insn) + pc;
                break;
	case 0b1100111: // I-type instruction
		 os << "jalr   x" << std::dec << get_rd(insn) << "," << get_imm_i(insn) << "(x" << get_rs1(insn) << ")";
                break;
	case 0b1100011: // B-type instruction
		switch(get_funct3(insn))	//using a switch statement for funct3 since opcode is same
		{
		case 0b000: os << "beq    "; break;
		case 0b001: os << "bne    "; break;
		case 0b100: os << "blt    "; break;
                case 0b101: os << "bge    "; break;
                case 0b110: os << "bltu   "; break;
                case 0b111: os << "bgeu   "; break;
                default:
                        os << "ERROR";
                        return os.str();
			break;
		}
		os << "x" << std::dec << get_rs1(insn) << ",x" << get_rs2(insn) << ",0x" << std::hex  <<(get_imm_b(insn)+ pc);
                break;

	case 0b0000011: // I-type instruction
		switch(get_funct3(insn))	 //using a switch statement for funct3 since opcode is same
		{
                case 0b000: os << "lb     "; break;
                case 0b001: os << "lh     "; break;
                case 0b010: os << "lw     "; break;
                case 0b100: os << "lbu    "; break;
                case 0b101: os << "lhu    "; break;
                default:
                        os << "ERROR";
                        return os.str();
			break;
		}
                os << "x" << std::dec << get_rd(insn) << "," << get_imm_i(insn) << "(x" << get_rs1(insn) << ")";
                break;

	case 0b0100011: // S-type instruction
		switch(get_funct3(insn))	//using a switch statement for funct3 since opcode is same
		{
                case 0b000: os << "sb     "; break;
                case 0b001: os << "sh     "; break;
                case 0b010: os << "sw     "; break;
                default:
                        os << "ERROR";
                        return os.str();
			break;
		}
		os << "x" << std::dec << get_rs2(insn) << "," << get_imm_s(insn) << "(x" << get_rs1(insn) << ")";
		break;

	case 0b0010011: // I-type instruction
                switch(get_funct3(insn))
                {
                case 0b000: os << "addi   "; break;
                case 0b010: os << "slti   "; break;
                case 0b011: os << "sltiu  "; break;
                case 0b100: os << "xori   "; break;
                case 0b110: os << "ori    "; break;
                case 0b111: os << "andi   "; break;
		case 0b001: os << "slli   "; break;
		case 0b101:
			switch(get_funct7(insn))	//using a switch statement for funct7 since opcode and funct3 are same.
			{
			case 0b0000000:
				os << "srli   ";
				insn = (insn & 0x01fffffff);	//to extract the shamt_i field
				break;
			case 0b0100000:
				os << "srai   ";
				insn = (insn & 0x01fffffff);	//to extract the shamt_i field
				break;
	                default:
      	              		os << "ERROR";
	                        return os.str();
				break;
			}
		os << "";
		break;
                default:
			os << "ERROR";
                        return os.str();
			break;
                }
                os << "x" << std::dec << get_rd(insn) << ",x" << get_rs1(insn) << "," << get_imm_i(insn);
                break;

	case 0b0110011: // R-type instruction
		switch(get_funct3(insn))	//using a switch statement for funct3 since opcode is the same.
		{
		case 0b000:
                        switch(get_funct7(insn))
                        {
                        case 0b0000000: os << "add    "; break;
                        case 0b0100000: os << "sub    "; break;
                        default:
	                        os << "ERROR";
                                return os.str();
				break;
                        }
		os << "";	//returning nothing to avoid any potential errors for not having anything in os.
		break;
		case 0b001: os << "sll    "; break;
                case 0b010: os << "slt    "; break;
                case 0b011: os << "sltu   "; break;
                case 0b100: os << "xor    "; break;
		case 0b101:
                        switch(get_funct7(insn))	//using a switch statement for funct7 since opcode and funct3 are the same.
                        {
                        case 0b0000000: os << "srl    "; break;
                        case 0b0100000: os << "sra    "; break;
                        default:
	                        os << "ERROR";
                                return os.str();
				break;
                        }
		os << "";
		break;
                case 0b110: os << "or     "; break;
                case 0b111: os << "and    "; break;
                default:
                        os << "ERROR";
                        return os.str();
			break;

		}
                os << "x" << std::dec << get_rd(insn) << ",x" << get_rs1(insn) << "(x" << get_rs2(insn) << ")";
                break;

	/*
	// This is for the fence instructions.
	// Print alphatets with respect to the bit positions for pred and succ in fence instruction.
	*/

	case 0b0001111: // fence instruction
		os <<"fence " << (insn&0x08000000?"i":"") << (insn&0x04000000?"o":"") <<(insn&0x02000000?"r":"") <<(insn&0x01000000?"w":"") << ","  << (insn&0x00800000?"i":"") << (insn&0x00400000?"o":"") <<(insn&0x00200000?"r":"")<<(insn&0x00100000?"w":"") ;
		break;
	case 0b1110011: // ecall and ebreak instructions
		switch(get_rs2(insn))
		{
		case 0b0000: os << "ecall  "; break;
		case 0b0001: os << "ebreak "; break;
		default:
			os << "ERROR";
			return os.str();
			break;
		}
                os << "";	//returning nothing to avoid any potential errors for not having anything in os.
                break;

	default:	//if no case matches return ERROR by default.
                os << "ERROR";
		break;

	}


	return os.str();	//return the output stream.
}

/*
// The run method will print the instructions from pc and decode method with pc as argument.
// It has a void return type and void argument.
*/

void rv32i::run(uint32_t limit)
{
regs.set(2, mem->get_size());
while(insn_counter < limit && !halt)
{
	dump();
	uint32_t insn = mem->get32(pc);
	cout << hex32(pc) << ": ";
	cout << std::setw(35) << std::setfill(' ') << std::left << decode(insn) << " /""/";
	cout << exec(insn) << endl;
	++insn_counter;
}
cout << insn_counter << " instructions executed." << endl;
dump();
}

std::string rv32i::exec_ebreak(uint32_t insn)
{
(void)insn;
halt = true;
return "HALT";
}

std::string rv32i::exec_lui(uint32_t insn)
{
 std::ostringstream os;
 uint32_t rd = get_rd(insn); // get the rd register number
 int32_t imm_u = get_imm_u(insn); // get the imm_u value
 regs.set(rd,imm_u); // store the imm_u value into rd
 pc += 4; // advance the pc past the end of this instruction

 // Return a string indicating the operation that has taken place
 os << std::dec << " x" << rd << " = " << hex0x32(imm_u);
 return os.str();
}



std::string rv32i::exec_auipc(uint32_t insn)
{
std::ostringstream os;
uint32_t rd = get_rd(insn);
int32_t imm_u = get_imm_u(insn);

regs.set(rd, pc + imm_u);

os << std::dec << " x" << rd << " = " << hex0x32(pc) << " + " << hex0x32(imm_u) << " = " << hex0x32(imm_u + pc);
pc += 4;
 return os.str();

}

std::string rv32i::exec_jal(uint32_t insn)
{
std::ostringstream os;
uint32_t rd = get_rd(insn);
uint32_t imm_j = get_imm_j(insn);

regs.set(rd,pc + 4);

os << std::dec << " x" << rd << " = " << hex0x32(imm_j) << ", pc = " << hex0x32(pc) << " + " << hex0x32(imm_j) << " = " << hex0x32(pc + imm_j);
pc = pc + imm_j;

 return os.str();

}


std::string rv32i::exec_jalr(uint32_t insn)
{
std::ostringstream os;
uint32_t rd = get_rd(insn);
uint32_t rs1 = get_rs1(insn);
int32_t imm_i = get_imm_i(insn);
uint32_t temp = pc+4;
regs.set(rd, pc + 4);
pc = ((rs1 + imm_i)&0xfffffffe);
os << std::dec << " x" << rd<< " = " << hex0x32(temp)  << ", pc = (" << hex0x32(regs.get(rs1)) << " + " << hex0x32(imm_i) << ") & " << "0xfffffffe" << " = " << hex0x32(pc);

 return os.str();

}

std::string rv32i::exec_beq(uint32_t insn)
{
std::ostringstream os;
uint32_t rs1 = get_rs1(insn);
uint32_t rs2 = get_rs2(insn);
uint32_t imm_b = get_imm_b(insn);
pc = pc + ((rs1 == rs2) ? imm_b : 4 );

os << std::dec << "pc +=" << hex0x32(regs.get(rs1)) << " == " <<  hex0x32(regs.get(rs2)) << " ? " << hex0x32(imm_b) << " : " << 4 << " = " << hex0x32(pc);
return os.str();
}

std::string rv32i::exec_bne(uint32_t insn)
{
std::ostringstream os;
uint32_t rs1 = get_rs1(insn);
uint32_t rs2 = get_rs2(insn);
uint32_t imm_b = get_imm_b(insn);

pc = pc + ((rs1 != rs2) ? imm_b : 4);

os << std::dec << "pc +=" << hex0x32(regs.get(rs1)) << " != " <<  hex0x32(regs.get(rs2)) << " ? " << hex0x32(imm_b) << " : " << 4 << " = " << hex0x32(pc);
return os.str();

}

std::string rv32i::exec_blt(uint32_t insn)
{
std::ostringstream os;
uint32_t rs1 = get_rs1(insn);
uint32_t rs2 = get_rs2(insn);
uint32_t imm_b = get_imm_b(insn);

pc = pc + ((rs1 < rs2) ? imm_b : 4);

os << std::dec << "pc +=" << hex0x32(regs.get(rs1))<< " < " <<  hex0x32(regs.get(rs2)) << " ? "<< hex0x32(imm_b)<< " : " << 4 << " = " << hex0x32(pc);

return os.str();

}

std::string rv32i::exec_bge(uint32_t insn)
{
std::ostringstream os;
uint32_t rs1 = get_rs1(insn);
uint32_t rs2 = get_rs2(insn);
uint32_t imm_b = get_imm_b(insn);

pc = pc + ((regs.get(rs1) >= regs.get(rs2)) ? imm_b : 4);

os << std::dec << "pc +=" << hex0x32(regs.get(rs1)) << " >= " <<  hex0x32(regs.get(rs2)) << " ? "<< hex0x32(imm_b)<< " : " << 4 << " = " << hex0x32(pc);

return os.str();

}

std::string rv32i::exec_bltu(uint32_t insn)
{
std::ostringstream os;
pc = pc + ((unsigned(regs.get(get_rs1(insn))) < unsigned(regs.get(get_rs2(insn)))) ? get_imm_b(insn) : 4);

os << std::dec << "pc +=" << hex0x32(regs.get(get_rs1(insn))) << " <U " <<  hex0x32(regs.get(unsigned(get_rs2(insn)))) << " ? "<< hex0x32(get_imm_b(insn))<< " : " << 4 << " = " << hex0x32(pc);
return os.str();
}

std::string rv32i::exec_bgeu(uint32_t insn)
{
std::ostringstream os;
pc = pc + ((unsigned(regs.get(get_rs1(insn))) >= unsigned(regs.get(get_rs2(insn)))) ? get_imm_b(insn) : 4);

os << std::dec << "pc +=" << hex0x32(regs.get(get_rs1(insn))) << " >=U " <<  hex0x32(regs.get(get_rs2(insn))) << " ? " << hex0x32(get_imm_b(insn))<< " : " << 4 << " = " << hex0x32(pc);
return os.str();

}

std::string rv32i::exec_lb(uint32_t insn)
{
std::ostringstream os;
uint32_t rd = get_rd(insn);
uint32_t imm_i = get_imm_i(insn);
uint32_t rs1 = get_rs1(insn);
uint32_t temp = mem->get8(regs.get(rs1) + imm_i);
if(temp & 0x00000080)
{
	temp |= 0xffffff00;
	os << std::dec << " x" << rd << " = sx(m8(" << hex0x32(regs.get(rs1)) << " + " << hex0x32(imm_i) << " = " << hex0x32(temp);
	regs.set(rd,mem->get8(regs.get(rs1) + imm_i));
}
else
{
        os << std::dec << " x" << rd << " = sx(m8(" << hex0x32(regs.get(rs1)) << " + " << hex0x32(imm_i) << " = " << hex0x32(temp);
}
pc +=  4;
return os.str();
}

std::string rv32i::exec_lh(uint32_t insn)
{

std::ostringstream os;
uint32_t rd = get_rd(insn);
uint32_t imm_i = get_imm_i(insn);
uint32_t rs1 = get_rs1(insn);
uint32_t temp = mem->get16(regs.get(rs1) + imm_i);
if(temp & 0x00000080)
{
        temp |= 0xffff0000;
	os << std::dec << " x" << rd << " = sx(m16(" << hex0x32(regs.get(get_rs1(insn))) << " + " << hex0x32(get_imm_i(insn)) << " = " << hex0x32(temp);
}
else
{
os << std::dec << " x" << rd << " = sx(m16(" << hex0x32(regs.get(get_rs1(insn))) << " + " << hex0x32(get_imm_i(insn)) << " = " << hex0x32(temp);
}
pc +=  4;
return os.str();


}

std::string rv32i::exec_lw(uint32_t insn)
{
std::ostringstream os;
uint32_t rd = get_rd(insn);
uint32_t imm_i = get_imm_i(insn);
uint32_t rs1 = get_rs1(insn);
uint32_t temp = mem->get32(regs.get(rs1) + imm_i);
os << std::dec << " x" << rd << " = sx(m32(" << hex0x32(regs.get(rs1)) << " + " << hex0x32(imm_i) << " = " << hex0x32(temp);
pc += 4;
return os.str();

}

std::string rv32i::exec_lbu(uint32_t insn)
{
std::ostringstream os;
uint32_t rd = get_rd(insn);
uint32_t imm_i = get_imm_i(insn);
uint32_t rs1 = get_rs1(insn);
uint32_t temp = mem->get8(regs.get(rs1) + imm_i);
os << std::dec << " x" << rd << " = zx(m8(" << hex0x32(regs.get(rs1)) << " + " << hex0x32(imm_i) << " = " << hex0x32(temp);
pc += 4;
return os.str();

}
std::string rv32i::exec_lhu(uint32_t insn)
{
std::ostringstream os;
uint32_t rd = get_rd(insn);
uint32_t imm_i = get_imm_i(insn);
uint32_t rs1 = get_rs1(insn);
uint32_t temp = mem->get16(regs.get(rs1) + imm_i);
os << std::dec << " x" << rd << " = zx(m16(" << hex0x32(regs.get(rs1)) << " + " << hex0x32(imm_i) << " = " << hex0x32(temp);
pc += 4;
return os.str();

}

std::string rv32i::exec_sb(uint32_t insn)
{
std::ostringstream os;
uint32_t rs1 = get_rs1(insn);
uint32_t rs2 = get_rs2(insn);
uint32_t imm_s = get_imm_s(insn);
uint32_t temp = rs1 + imm_s;
mem->set8(temp,rs2&0xff);

os << std::dec << " m8(" << hex0x32(regs.get(rs1)) << " + " << hex0x32(imm_s) << " = " << hex0x32(temp);
pc += 4;

return os.str();
}

std::string rv32i::exec_sh(uint32_t insn)
{
std::ostringstream os;
uint32_t rs1 = get_rs1(insn);
uint32_t rs2 = get_rs2(insn);
uint32_t imm_s = get_imm_s(insn);
uint32_t temp = rs1 + imm_s;
mem->set16(temp,rs2&0xffff);

os << std::dec <<" m16(" << hex0x32(regs.get(rs1)) << " + " << hex0x32(imm_s) << " = " << hex0x32(temp);
pc += 4;

return os.str();

}
std::string rv32i::exec_sw(uint32_t insn)
{
std::ostringstream os;
uint32_t rs1 = get_rs1(insn);
uint32_t rs2 = get_rs2(insn);
uint32_t imm_s = get_imm_s(insn);
uint32_t temp = rs1 + imm_s;
 mem->set32(temp, rs2&0xffffffff);

os << std::dec << " m32(" << hex0x32(regs.get(rs1)) << " + " << hex0x32(imm_s) << " = " << hex0x32(temp);
pc += 4;

return os.str();

}

std::string rv32i::exec_addi(uint32_t insn)
{
std::ostringstream os;
int32_t rd = get_rd(insn);
int32_t imm_i = get_imm_i(insn);
int32_t rs1 = get_rs1(insn);
int32_t temp1 = (regs.get(rs1) + imm_i);


regs.set(rd, temp1);
os << std::dec << " x" << rd << " = " <<  hex0x32(regs.get(rs1)) << " + " << hex0x32(imm_i) << " = " << hex0x32(temp1);


pc += 4;

return os.str();
}

std::string rv32i::exec_slti(uint32_t insn)
{
std::ostringstream os;
uint32_t rd = get_rd(insn);
uint32_t imm_i = get_imm_i(insn);
uint32_t rs1 = get_rs1(insn);
uint32_t temp1 = ((rs1 < imm_i) ? 1 : 0);
regs.set(rd, temp1);

os << std::dec << " x" << rd << " = " <<  hex0x32(regs.get(rs1)) << " < " << hex0x32(imm_i) << " ? " << "1 " << " : " << "0" << " = " << hex0x32(temp1);
pc += 4;

return os.str();

}
std::string rv32i::exec_sltiu(uint32_t insn)
{
std::ostringstream os;
uint32_t rd = get_rd(insn);
uint32_t imm_i = get_imm_i(insn);
uint32_t rs1 = get_rs1(insn);
uint32_t temp1 = ((unsigned(regs.get(rs1)) < imm_i) ? 1 : 0);
regs.set(rd, temp1);
os << std::dec << " x" << rd << " = " <<  hex0x32(regs.get(rs1)) << " <U " << hex0x32(imm_i) << " ? " << "1  " << " : " << "0" << " = " << hex0x32(temp1);
pc += 4;

return os.str();


}
std::string rv32i::exec_xori(uint32_t insn)
{
std::ostringstream os;
uint32_t rd = get_rd(insn);
uint32_t imm_i = get_imm_i(insn);
uint32_t rs1 = get_rs1(insn);
uint32_t temp1 = ((regs.get(rs1)^imm_i));
regs.set(rd, temp1);
os << std::dec << " x" << rd << " = " <<  hex0x32(regs.get(rs1)) << " ^ " << hex0x32(imm_i) << " = " << hex0x32(temp1);
pc += 4;

return os.str();



}
std::string rv32i::exec_ori(uint32_t insn)
{
std::ostringstream os;
uint32_t rd = get_rd(insn);
uint32_t imm_i = get_imm_i(insn);
uint32_t rs1 = get_rs1(insn);
uint32_t temp1 =  ((regs.get(rs1) | imm_i));
regs.set(rd, temp1);
os << std::dec << " x" << rd << " = " <<  hex0x32(regs.get(rs1)) << " | " << hex0x32(imm_i) << " = " << hex0x32(temp1);
pc += 4;

return os.str();



}
std::string rv32i::exec_andi(uint32_t insn)
{
std::ostringstream os;
uint32_t rd = get_rd(insn);
uint32_t imm_i = get_imm_i(insn);
uint32_t rs1 = get_rs1(insn);
uint32_t temp1 = ((regs.get(rs1) & imm_i));
regs.set(rd, temp1);
os << std::dec << " x" << rd << " = " <<  hex0x32(regs.get(rs1)) << " & " << hex0x32(imm_i) << " = " << hex0x32(temp1);
pc += 4;

return os.str();



}

std::string rv32i::exec_slli(uint32_t insn)
{
std::ostringstream os;
uint32_t shamt = (insn & 0x01ffffff);
uint32_t shamt_i = get_imm_i(shamt);
uint32_t rd = get_rd(insn);
uint32_t rs1 = get_rs1(insn);
uint32_t temp = regs.get(rs1)<<shamt_i;
regs.set(rd, temp);
os << std::dec << " x" << rd << " = " << hex0x32(regs.get(rs1)) << " >> " << shamt_i << " = " << hex0x32(temp);
pc += 4;
return os.str();
}

std::string rv32i::exec_srli(uint32_t insn)
{
std::ostringstream os;
uint32_t shamt = (insn & 0x01ffffff);
uint32_t shamt_i = get_imm_i(shamt);
uint32_t rd = get_rd(insn);
uint32_t rs1 = get_rs1(insn);
uint32_t temp = regs.get(rs1)>>shamt_i;
regs.set(rd, temp);
os << std::dec << " x" << rd << " = " << hex0x32(regs.get(rs1)) << " >> " << shamt_i << " = " << hex0x32(temp);
pc += 4;
return os.str();
}

std::string rv32i::exec_srai(uint32_t insn)
{
std::ostringstream os;
uint32_t shamt = (insn & 0x01ffffff);
uint32_t shamt_i = get_imm_i(shamt);
uint32_t rd = get_rd(insn);
int32_t rs1 = get_rs1(insn);
uint32_t temp = regs.get(rs1)>>shamt_i;
regs.set(rd, temp);
os << std::dec << " x" << rd << " = " << hex0x32(regs.get(rs1)) << " >> " << shamt_i << " = " << hex0x32(temp);
pc += 4;
return os.str();

}

std::string rv32i::exec_add(uint32_t insn)
{
std::ostringstream os;
uint32_t rd = get_rd(insn);
uint32_t rs1 = get_rs1(insn);
uint32_t rs2 = get_rs2(insn);
uint32_t temp = regs.get(rs1)+regs.get(rs2);
regs.set(rd, temp);
os << std::dec << " x" << rd << hex0x32(regs.get(rs1)) << " + " << hex0x32(regs.get(rs2)) << hex0x32(temp);
pc += 4;
return os.str();
}

std::string rv32i::exec_sub(uint32_t insn)
{
std::ostringstream os;
uint32_t rd = get_rd(insn);
uint32_t rs1 = get_rs1(insn);
uint32_t rs2 = get_rs2(insn);
uint32_t temp = regs.get(rs1)-regs.get(rs2);
regs.set(rd, temp);
os << std::dec << " x" << rd << hex0x32(regs.get(rs1)) << " + " << hex0x32(regs.get(rs2)) << hex0x32(temp);
pc += 4;
return os.str();

}
std::string rv32i::exec_sll(uint32_t insn)
{
std::ostringstream os;
uint32_t rd = get_rd(insn);
uint32_t rs1 = get_rs1(insn);
uint32_t rs2 = get_rs2(insn);
uint32_t temp = regs.get(rs1)<<((regs.get(rs2)%XLEN));
uint32_t temp1 = ((regs.get(rs2)%XLEN));
regs.set(rd, temp);
os << std::dec << " x" << rd << regs.get(rs1) << " << " << hex0x32(temp1) << " = " << hex0x32(temp);
pc += 4;
return os.str();
}

std::string rv32i::exec_slt(uint32_t insn)
{
std::ostringstream os;
uint32_t rd = get_rd(insn);
uint32_t rs1 = get_rs1(insn);
uint32_t rs2 = get_rs2(insn);
uint32_t temp = (regs.get(rs1)<regs.get(rs2) ? 1 : 0);
regs.set(rd, temp);
os << std::dec << " x" << rd << " =(" << hex0x32(regs.get(rs1)) << " < " << hex0x32(regs.get(rs2)) << " ? " << "1 " << ": " << "0 " << " = " << hex0x32(temp); 
pc += 4;
return os.str();
}

std::string rv32i::exec_sltu(uint32_t insn)
{
std::ostringstream os;
uint32_t rd = get_rd(insn);
uint32_t rs1 = get_rs1(insn);
uint32_t rs2 = get_rs2(insn);
uint32_t temp = (regs.get(rs1)<regs.get(rs2) ? 1 : 0);
regs.set(rd, temp);
os << std::dec << " x" << rd << " =(" << hex0x32(regs.get(rs1)) << " < " << hex0x32(regs.get(rs2)) << " ? " << "1 " << ": " << "0 " << " = " << hex0x32(temp);
pc += 4;
return os.str();

}
std::string rv32i::exec_xor(uint32_t insn)
{
std::ostringstream os;
uint32_t rd = get_rd(insn);
uint32_t rs1 = get_rs1(insn);
uint32_t rs2 = get_rs2(insn);
uint32_t temp1 = ((regs.get(rs1)^regs.get(rs2)));
regs.set(rd, temp1);
os << std::dec << " x" << rd << " = " <<  hex0x32(regs.get(rs1)) << " ^ " << hex0x32(regs.get(rs2)) << " = " << hex0x32(temp1);
pc += 4;

return os.str();



}
std::string rv32i::exec_srl(uint32_t insn)
{
std::ostringstream os;
uint32_t rd = get_rd(insn);
uint32_t rs1 = get_rs1(insn);
uint32_t rs2 = get_rs2(insn);
uint32_t temp = regs.get(rs1)>>((regs.get(rs2)%XLEN));
uint32_t temp1 = ((regs.get(rs2)%XLEN));
regs.set(rd, temp);
os << std::dec << " x" << rd << hex0x32(regs.get(rs1)) << " << " << hex0x32(temp1) << " = " << hex0x32(temp);
pc += 4;
return os.str();

}
std::string rv32i::exec_sra(uint32_t insn)
{
std::ostringstream os;
uint32_t rd = get_rd(insn);
int32_t rs1 = get_rs1(insn);
uint32_t rs2 = get_rs2(insn);
uint32_t temp = regs.get(rs1)>>((regs.get(rs2)%XLEN));
uint32_t temp1 = ((regs.get(rs2)%XLEN));
regs.set(rd, temp);
os << std::dec << " x" << rd << hex0x32(regs.get(rs1)) << " >> " << hex0x32(temp1) << " = " << hex0x32(temp);
pc += 4;
return os.str();

}
std::string rv32i::exec_or(uint32_t insn)
{
std::ostringstream os;
uint32_t rs1 = get_rs1(insn);
uint32_t rs2 = get_rs2(insn);
uint32_t rd = get_rd(insn);
uint32_t temp = regs.get(rs1) | regs.get(rs2);
regs.set(rd,temp);
os << std::dec << " x" << rd << " = " << hex0x32(regs.get(rs1)) << " | " << hex0x32(regs.get(rs2)) << " = " << hex0x32(temp);
pc += 4;
return os.str();
}
std::string rv32i::exec_and(uint32_t insn)
{
std::ostringstream os;
uint32_t rs1 = get_rs1(insn);
uint32_t rs2 = get_rs2(insn);
uint32_t rd = get_rd(insn);
uint32_t temp = regs.get(rs1) & regs.get(rs2);
regs.set(rd,temp);
os << std::dec << " x" << rd << " = " << hex0x32(regs.get(rs1)) << " & " << hex0x32(regs.get(rs2)) << " = " << hex0x32(temp);
pc += 4;
return os.str();

}

std::string rv32i::exec_fence(uint32_t insn)
{
std::ostringstream os;
os <<"fence " << (insn&0x08000000?"i":"") << (insn&0x04000000?"o":"") <<(insn&0x02000000?"r":"") <<(insn&0x01000000?"w":"") << ","  << (insn&0x00800000?"i":"") << (insn&0x00400000?"o":"") <<(insn&0x00200000?"r":"")<<(insn&0x00100000?"w":"") ;
pc +=4;
return os.str();
}


std::string rv32i::exec(uint32_t insn)
{
	uint32_t opcode = get_opcode(insn);
	uint32_t funct3 = get_funct3(insn);
	uint32_t funct7 = get_funct7(insn);
	switch(opcode)
	{
	case 0b0110111: return exec_lui(insn);break;
	case 0b0010111: return exec_auipc(insn);break;
	case 0b1101111: return exec_jal(insn);break;
	case 0b1100111: return exec_jalr(insn);break;
	case 0b1100011:
		switch(funct3)
		{
		case 0b000: return exec_beq(insn);break;
		case 0b001: return exec_bne(insn);break;
		case 0b100: return exec_blt(insn);break;
		case 0b101: return exec_bge(insn);break;
		case 0b110: return exec_bltu(insn);break;
		case 0b111: return exec_bgeu(insn);break;
		}
		break;
	case 0b0000011:
		switch(funct3)
		{
		case 0b000: return exec_lb(insn); break;
                case 0b001: return exec_lh(insn); break;
                case 0b010: return exec_lw(insn); break;
                case 0b100: return exec_lbu(insn); break;
                case 0b101: return exec_lhu(insn); break;
		}
		break;
	case 0b0100011:
		switch(funct3)
		{
		case 0b000: return exec_sb(insn); break;
		case 0b001: return exec_sh(insn); break;
		case 0b010: return exec_sw(insn); break;
		}
		break;
	case 0b0010011:
		switch(funct3)
		{
                case 0b000: return exec_addi(insn); break;
                case 0b010: return exec_slti(insn); break;
                case 0b011: return exec_sltiu(insn);break;
                case 0b100: return exec_xori(insn); break;
                case 0b110: return exec_ori(insn);  break;
                case 0b111: return exec_andi(insn); break;
		case 0b001: return exec_slli(insn); break;
		case 0b101:
			switch(funct7)
			{
			case 0b0000000: return exec_srli(insn);break;
			case 0b0100000: return exec_srai(insn);break;
			}
			break;
		}
    		break;
	case 0b0110011:
		switch(funct3)
		{
		case 0b000:
			switch(funct7)
			{
                        case 0b0000000: return exec_add(insn);break;
                        case 0b0100000: return exec_sub(insn);break;
                        }
			break;
                case 0b001:return exec_sll(insn); break;
                case 0b010:return exec_slt(insn); break;
                case 0b011:return exec_sltu(insn);break;
                case 0b100:return exec_xor(insn); break;
                case 0b101:
                        switch(get_funct7(insn))        //using a switch statement for funct7 since opcode and funct$
                        {
                        case 0b0000000: return exec_srl(insn);break;
                        case 0b0100000: return exec_sra(insn);break;
                        }
	                break;
                case 0b110: return exec_or(insn);break;
                case 0b111: return exec_and(insn);break;
		}
		break;

	case 0b0001111: return exec_fence(insn);break;

	case 0b1110011:
		if(insn & 0x00100000)
		  return exec_ebreak(insn);
		else
		  return exec_ebreak(insn);
		break;
	}

	pc += 4;
	halt = true;
	return "ERROR:unimplimented instructions";

}

// The get_opcode method will extract the opcode of the passed in instruction.
// this method will take a memory instruction as argument and extract its opcode.


uint32_t rv32i::get_opcode(uint32_t insn)
{

	return (insn & 0x7f);

}

/*
// The get_rd method will extract the rd of the passed in instruction.
// this method will take a memory instruction as argument and extract its rd.
*/

uint32_t rv32i::get_rd(uint32_t insn)
{

	return (insn & 0xf80)>>(7-0);

}

/*
// The get_funct3 method will extract the funct3 field of the passed in instruction.
// this method will take a memory instruction as argument and extract its funct3 field.
*/

uint32_t rv32i::get_funct3(uint32_t insn)
{

	return (insn & 0x7000)>>(12-0);

}

/*
 The get_rs1 method will extract the rs1 register field of the passed in instruction.
 this method will take a memory instruction as argument and extract its rs1.
*/

uint32_t rv32i::get_rs1(uint32_t insn)
{

	return (insn & 0xf8000)>>(15-0);

}

/*
 The get_2 method will extract the rs2 register field of the passed in instruction.
 this method will take a memory instruction as argument and extract its rs2.
*/

uint32_t rv32i::get_rs2(uint32_t insn)
{

	return(insn & 0x1f00000)>>(20-0);

}

/*
 The get_funct7 method will extract the funct7 field of the passed in instruction.
 this method will take a memory instruction as argument and extract its funct7 field
*/

uint32_t rv32i::get_funct7(uint32_t insn)
{

	return (insn & 0xfe000000)>>(25-0);

}

/*
 The get_imm_i method will return the imm_i field of the passed in I-type instruction.
 this method will take a memory instruction as argument and return its imm_i instruction.
*/

int32_t rv32i::get_imm_i(uint32_t insn)
{
int32_t imm_i;

imm_i = (insn & 0x01f00000)>>(20-0);
imm_i |= (insn & 0xfe000000)>>(25-5);

if(insn & 0x80000000)
	imm_i |= 0xfffff000;

return imm_i;
}

/*
 The get_imm_u method will return the imm_u field of the passed in U-type instruction.
 this method will take a memory instruction as argument and return its imm_u instruction.
*/

int32_t rv32i::get_imm_u(uint32_t insn)
{
int32_t imm_u = (insn & 0xfffff000)>>(12-12);

return imm_u;
}

/*
 The get_imm_b method will return the imm_b field of the passed in B-type instruction.
 this method will take a memory instruction as argument and return its imm_b instruction.
*/

int32_t rv32i::get_imm_b(uint32_t insn)
{
uint32_t imm_b = (insn & 0x80000000)>>(31-12);
imm_b |= (insn & 0x7e000000)>>(25-5);
imm_b |= (insn & 0xf00)>>(8-1);
imm_b |= (insn & 0x80)<<(4);

if(insn & 0x80000000)
	imm_b |= 0xfffff000;

return imm_b;
}

/*
 The get_imm_s method will return the imm_s field of the passed in S-type instruction.
 this method will take a memory instruction as argument and return its imm_s instruction.
*/

int32_t rv32i::get_imm_s(uint32_t insn)
{

int32_t imm_s = (insn & 0xfe000000)>>(25-5);
imm_s |= (insn & 0x00000f80)>>(7-0);

if(insn & 0x80000000)
	imm_s |= 0xfffff000;

return imm_s;

}

/*
 The get_imm_j method will return the imm_j field of the passed in J-type instruction.
 this method will take a memory instruction as argument and return its imm_j instruction.
*/

int32_t rv32i::get_imm_j(uint32_t insn)
{
int32_t imm_j = (insn & 0x100000)>>(20-11);
imm_j |= (insn & 0x7fe00000)>>(21-1);
imm_j |= (insn & 0xff000)>>(12-12);
imm_j |= (insn & 0x80000000)>>(31-20);

if(insn & 0x80000000)		//sign-extend
	imm_j |= 0xfff00000;

return imm_j;
}

void rv32i::dump() const
{
regs.dump();
cout << endl << " pc :" << hex32(pc);
cout << endl;
}
