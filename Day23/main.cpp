/************************************************************************/
/* Advent of Code:
/* Day 23: Opening the Turing Lock
/************************************************************************/

#include <type_traits>
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <array>
#include <map>

class CEmu
{
public:
	CEmu() : m_reg() {};
	CEmu(int reg) { m_reg[0] = reg; m_reg[1] = 0; };
	~CEmu() {};
	void execute();
	int getReg(int idx) { return m_reg[idx]; };
	void setReg(int idx, int value) { m_reg[idx] = value; };
	void insertInstr(std::string& line, int idx);
	void reset() { m_ip = 0; m_reg[0] = 0; m_reg[1] = 0; };

public:
	enum INSTRUCTION {
		HLF = 0,
		TPL,
		INC,
		JMP,
		JIE,
		JIO,
		ERR
	};

	struct OPCODE {
		INSTRUCTION	instr;
		int*		reg;
		int*		ip;
		int			off;
	};

	INSTRUCTION str2instr(std::string& name);

private:
	std::map<int, CEmu::OPCODE> m_codeBlock;
	int		m_ip;
	int		m_reg[2];
};

void CEmu::execute()
{
	using FUNC = std::add_pointer<void(OPCODE& opcode)>::type;
	FUNC hlf = [](OPCODE& opcode) -> void { *(opcode.reg) >>= 1; (*(opcode.ip))++; return; };
	FUNC tpl = [](OPCODE& opcode) -> void { *(opcode.reg) = (*(opcode.reg) << 1) + *(opcode.reg); (*(opcode.ip))++; return; };
	FUNC inc = [](OPCODE& opcode) -> void { (*(opcode.reg))++; (*(opcode.ip))++; return; };
	FUNC jmp = [](OPCODE& opcode) -> void { (*(opcode.ip)) += opcode.off; return; };
	FUNC jie = [](OPCODE& opcode) -> void { if (((*(opcode.reg)) & 1) == 0) { (*(opcode.ip)) += opcode.off; } else { (*(opcode.ip))++; } return; };
	FUNC jio = [](OPCODE& opcode) -> void { if ((*(opcode.reg)) == 1) { (*(opcode.ip)) += opcode.off; } else { (*(opcode.ip))++; } return; };

	std::array<FUNC, 6> functions = {
		hlf, tpl, inc, jmp, jie, jio
	};

	while (m_codeBlock.find(m_ip) != m_codeBlock.end())
	{
		CEmu::OPCODE opc = m_codeBlock[m_ip];
		functions[opc.instr](opc);
	}
	return;
}

CEmu::INSTRUCTION CEmu::str2instr(std::string& name)
{
	if (name == "hlf")
		return HLF;
	if (name == "tpl")
		return TPL;
	if (name == "inc")
		return INC;
	if (name == "jmp")
		return JMP;
	if (name == "jie")
		return JIE;
	if (name == "jio")
		return JIO;
	return ERR;
}


void CEmu::insertInstr(std::string& line, int idx)
{
	CEmu::OPCODE op;
	std::string ins = line.substr(0, 3);
	char reg = line[4];
	op.reg = &m_reg[((reg == 'b') ? 1 : 0)];
	op.ip = &m_ip;
	op.instr = str2instr(ins);
	switch (op.instr)
	{
	case JMP:
		op.off = std::stoi(line.substr(4, 7));
		break;
	case JIO:
	case JIE:
		op.off = std::stoi(line.substr(7, 10));
		break;
	default:
		op.off = 0;
		break;
	}
	m_codeBlock[idx] = op;
}

int partOne(CEmu& emu)
{
	emu.reset();
	emu.execute();
	return emu.getReg(1);
}

int partTwo(CEmu& emu)
{
	emu.reset();
	emu.setReg(0, 1);
	emu.execute();
	return emu.getReg(1);
}

void readData(CEmu& emu)
{
	std::ifstream infile("data_d23.txt");
	std::string input;
	int idx = 0;

	while (std::getline(infile, input))
	{
		emu.insertInstr(input, idx++);
	}
	return;
}

int main()
{
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	CEmu emu;
	readData(emu);
	std::cout << "Part One: " << partOne(emu) << std::endl;
	std::cout << "Part Two: " << partTwo(emu) << std::endl;
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	std::cout << "Time: " << time_span.count() << "s.";
	return 0;
}
