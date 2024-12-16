/*Name - Chaitanya Saagar
Roll number -2301CS77*/

#include<bits/stdc++.h>
using namespace std;

string dechex(int decimal) {
    string hexResult;
    // Iterate 8 times to process all potential hex digits (for a 32-bit integer)
    for (int i = 0; i < 8; i++, decimal >>= 4) {
        int hexDigit = decimal & 15; // Extract the last 4 bits (equivalent to decimal % 16)

        // Append the corresponding hex character ('0'-'9' for 0-9, 'a'-'f' for 10-15)
        hexResult += (hexDigit < 10) ? (hexDigit + '0') : (hexDigit - 10 + 'a');
    }
    
    // Reverse the string to get the correct hex representation
    reverse(hexResult.begin(), hexResult.end());
    return hexResult; // Return the final hex string
}

int mem[20000005]; // Array to store memory contents
int pc, sp, a, b;  // Registers for program counter, stack pointer, and general-purpose

vector<int> machinecodes; // Vector to store machine codes

struct MemoryRead {
    int address, value;
};
vector<MemoryRead> reads; // Vector to store memory read operations

struct MemoryWrite {
    int address, oldValue, newValue;
};
vector<MemoryWrite> writes; // Vector to store memory write operations


//Follwing function traces the .o file whole and last tells total instruction or segmentation fault
void trace(int size) {
    pc = 0;
    int cnt = 0;
    bool halt = false, error = false;

    while (pc < size) {
        int instr = machinecodes[pc];
        int type = instr & 0xFF; // Extract type (lower 8 bits)
        int offset = (instr >> 8) & 0x7FFFFF; // Extract offset (bits 8-30)
        if (instr & (1 << 31)) offset -= (1 << 23); // Adjust for negative offset if needed
        
        int prev = -1;
        switch (type) {
            case 0: b = a; a = offset; break;
            case 1: a += offset; break;
            case 2: b = a; a = mem[sp + offset]; reads.push_back({sp + offset, a}); break;
            case 3: prev = mem[sp + offset]; mem[sp + offset] = a; a = b; writes.push_back({sp + offset, prev, a}); break;
            case 4: prev = a; a = mem[a + offset]; reads.push_back({prev + offset, a}); break;
            case 5: prev = mem[a + offset]; mem[a + offset] = b; writes.push_back({a + offset, prev, b}); break;
            case 6: a = b + a; break;
            case 7: a = b - a; break;
            case 8: a = b << a; break;
            case 9: a = b >> a; break;
            case 10: sp += offset; break;
            case 11: sp = a; a = b; break;
            case 12: b = a; a = sp; break;
            case 13: b = a; a = pc; pc += offset; break;
            case 14: pc = a; a = b; break;
            case 15: if (a == 0) pc += offset; break;
            case 16: if (a < 0) pc += offset; break;
            case 17: pc += offset; break;
            case 18: halt = true; break;
        }

        pc++;
        cout << "PC= " << dechex(pc) << " SP= " << dechex(sp) << " A= " << dechex(a) << " B= " << dechex(b) << "\n";

        if (pc < 0 || cnt > (1 << 24)) {
            error = true;
            break;
        }
        cnt++;
        if (halt) break;
    }

    if (error) {
        cout << "Segmentation fault or some other error\n";
        exit(0);
    }

    cout << "Total instructions ran are\n" << cnt << "\n";
}

//Following function displays all possible commands
void showisa()
{
	cout<<"Opcode Mnemonic Operand"<<'\n';
	cout<<"0      ldc      value "<<"\n";
	cout<<"1      adc      value "<<"\n";
	cout<<"2      ldl      value "<<"\n";
	cout<<"3      stl      value "<<"\n";
	cout<<"4      ldnl     value "<<"\n";
	cout<<"5      stnl     value "<<"\n";
	cout<<"6      add            "<<"\n";
	cout<<"7      sub            "<<"\n";
	cout<<"9      shr            "<<"\n";
	cout<<"10     adj      value "<<"\n";
	cout<<"11     a2sp           "<<"\n";
	cout<<"12     sp2a           "<<"\n";
	cout<<"13     call     offset"<<"\n";
	cout<<"14     return         "<<"\n";
	cout<<"15     brz      offset"<<"\n";
	cout<<"16     brlz     offset"<<"\n";
	cout<<"17     br       offset"<<"\n";
	cout<<"18     HALT           "<<"\n";
	cout<<"       SET      value "<<"\n";
}

int32_t main() {
    // Input file name
    string fileName;
    cout << "Enter the file name (with extension) to run the emulator:\n";
    cin >> fileName;

    // Read the binary file and store machine codes
    ifstream file(fileName, ios::in | ios::binary);
    unsigned int cur;
    while (file.read((char*)&cur, sizeof(int))) {
        machinecodes.push_back(cur);
        mem[machinecodes.size() - 1] = cur;
    }

    int size = machinecodes.size();
    
    // Menu-driven program
    while (true) {
        cout << "\nMENU\n"
             << "1: Get trace\n"
             << "2: Display ISA(Instruction set architecture)\n"
             << "3: Reset registers\n"
             << "4: Memory dump before execution\n"
             << "5: Memory dump after execution\n"
             << "6: Show memory reads\n"
             << "7: Show memory writes\n"
             << "8 or greater: Exit\n\n"
             << "Enter your choice: ";
        
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                trace(size);
                break;
            case 2:
                showisa();
                break;
            case 3:
                a = b = pc = sp = 0;
                break;
            case 4:
                cout << "Memory dump before execution\n";
                for (int i = 0; i < size; i += 4) {
                    cout << dechex(i) << " ";
                    for (int j = i; j < min(size, i + 4); ++j) 
                        cout << dechex(machinecodes[j]) << " ";
                    cout << "\n";
                }
                break;
            case 5:
                cout << "Memory dump after execution\n";
                for (int i = 0; i < size; i += 4) {
                    cout << dechex(i) << " ";
                    for (int j = i; j < min(size, i + 4); ++j) 
                        cout << dechex(mem[j]) << " ";
                    cout << "\n";
                }
                break;
            case 6:
                for (const auto& read : reads)
                    cout << "Read memory[" << dechex(read.address) << "] found " << dechex(read.value) << "\n";
                break;
            case 7:
                for (const auto& write : writes)
                    cout << "Wrote memory[" << dechex(write.address) << "] was " << dechex(write.oldValue) << " now " << dechex(write.newValue) << "\n";
                break;
            default:
                return 0;
        }
    }
}