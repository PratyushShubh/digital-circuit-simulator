/**
 * @file circuit.cpp
 * @brief Digital Circuit Simulator - A C++ program for simulating and visualizing digital logic circuits
 * @author Piyush
 * @date September 2025
 * @version 1.0
 * 
 * This program allows users to:
 * - Define digital logic circuits with various gate types
 * - Simulate circuit behavior with different input combinations
 * - Generate visual circuit diagrams using Graphviz
 * - Export circuit descriptions as DOT files
 */

#include <iostream>     // For input/output operations
#include <fstream>      // For file operations (DOT file generation)
#include <vector>       // For dynamic arrays (storing gates)
#include <unordered_map>// For hash maps (not used but included for compatibility)
#include <string>       // For string operations
#include <sstream>      // For string stream operations (parsing input)
#include <map>          // For ordered maps (storing net values)
#include <set>          // For sets (storing primary inputs/outputs)
#include <cstdlib>      // For system() function calls
#include <algorithm>    // For transform function (case conversion)
#include <cctype>       // For toupper function

using namespace std;

/**
 * @struct Gate
 * @brief Represents a digital logic gate with its type, output, and inputs
 */
struct Gate {
    string type;            ///< Gate type (AND, OR, NOT, etc.)
    string out;             ///< Output net name
    vector<string> inputs;  ///< Input net names
};

// Global variables for circuit representation
map<string, int> values;        ///< Stores current values of all nets (0 or 1)
vector<Gate> gates;             ///< List of all gates in the circuit
set<string> primaryInputs;      ///< Set of primary input net names
set<string> primaryOutputs;     ///< Set of primary output net names

/**
 * @brief Evaluates a logic gate based on its type and input values
 * @param g The gate to evaluate
 * @return The output value (0 or 1) of the gate
 */
int evalGate(const Gate &g) {
    // Two-input gates
    if (g.type == "AND") 
        return values[g.inputs[0]] & values[g.inputs[1]];
    if (g.type == "OR")  
        return values[g.inputs[0]] | values[g.inputs[1]];
    if (g.type == "NAND") 
        return !(values[g.inputs[0]] & values[g.inputs[1]]);
    if (g.type == "NOR")  
        return !(values[g.inputs[0]] | values[g.inputs[1]]);
    if (g.type == "XOR") 
        return values[g.inputs[0]] ^ values[g.inputs[1]];
    if (g.type == "XNOR") 
        return !(values[g.inputs[0]] ^ values[g.inputs[1]]);
    
    // Single-input gate
    if (g.type == "NOT") 
        return !values[g.inputs[0]];
    
    // Error handling for unknown gate types
    cerr << "Error: Unknown gate type: " << g.type << "\n";
    return 0;
}

/**
 * @brief Simulates the entire circuit by evaluating all gates
 * 
 * This function propagates values through all gates in the circuit.
 * Gates are evaluated in the order they were defined, which assumes
 * proper topological ordering by the user.
 */
void simulate() {
    for (auto &g : gates) {
        values[g.out] = evalGate(g);
    }
}

/**
 * @brief Generates a Graphviz DOT file for circuit visualization
 * @param circuitName Name of the circuit (used for file naming)
 * 
 * Creates a .dot file that can be used with Graphviz to generate
 * visual circuit diagrams. Also attempts to automatically generate
 * a PNG image if Graphviz is installed.
 */
void writeDot(const string &circuitName) {
    string filename = circuitName + ".dot";
    ofstream dot(filename);
    
    // Check if file creation was successful
    if (!dot.is_open()) {
        cout << "Error: Could not create DOT file '" << filename << "'.\n";
        return;
    }
    
    // Write DOT file header
    dot << "digraph " << circuitName << " {\n";
    dot << "    // Graph properties\n";
    dot << "    rankdir=LR;  // Left to right layout\n";
    dot << "    node [shape=box, style=filled, color=lightblue];\n";
    dot << "    \n";
    
    // Add primary inputs as special nodes
    dot << "    // Primary inputs\n";
    for (const auto& input : primaryInputs) {
        dot << "    " << input << " [color=lightgreen, label=\"" << input << "\\nIN\"];\n";
    }
    dot << "    \n";
    
    // Add primary outputs as special nodes
    dot << "    // Primary outputs\n";
    for (const auto& output : primaryOutputs) {
        dot << "    " << output << " [color=lightcoral, label=\"" << output << "\\nOUT\"];\n";
    }
    dot << "    \n";
    
    // Add gates and connections
    dot << "    // Gates and connections\n";
    for (size_t i = 0; i < gates.size(); i++) {
        const auto &g = gates[i];
        string gateNode = "gate_" + to_string(i) + "_" + g.type;
        
        // Create gate node
        dot << "    " << gateNode << " [label=\"" << g.type << "\", color=lightyellow];\n";
        
        // Connect inputs to gate
        for (const auto &input : g.inputs) {
            dot << "    " << input << " -> " << gateNode << ";\n";
        }
        
        // Connect gate to output
        dot << "    " << gateNode << " -> " << g.out << ";\n";
    }
    
    dot << "}\n";
    dot.close();
    
    cout << "✓ DOT file saved as '" << filename << "'\n";
    
    // Attempt to generate PNG with Graphviz
    string cmd = "dot -Tpng \"" + filename + "\" -o \"" + circuitName + ".png\"";
    cout << "Attempting to generate circuit diagram...\n";
    
    int result = system(cmd.c_str());
    if (result == 0) {
        cout << "✓ Circuit diagram saved as '" << circuitName << ".png'\n";
    } else {
        cout << "⚠ Graphviz 'dot' command not found.\n";
        cout << "  Install Graphviz (https://graphviz.org/) to generate circuit diagrams.\n";
        cout << "  You can still use the .dot file for manual visualization.\n";
    }
}

/**
 * @brief Converts a string to uppercase for case-insensitive comparisons
 * @param str Input string
 * @return Uppercase version of the input string
 */
string toUpper(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

/**
 * @brief Validates if a gate type is supported
 * @param type Gate type to validate
 * @return true if the gate type is supported, false otherwise
 */
bool isValidGateType(const string& type) {
    return type == "AND" || type == "OR" || type == "NAND" || type == "NOR" || 
           type == "XOR" || type == "XNOR" || type == "NOT";
}

/**
 * @brief Gets the required number of inputs for a specific gate type
 * @param type Gate type
 * @return Number of required inputs, or -1 if invalid gate type
 */
int getRequiredInputs(const string& type) {
    if (type == "NOT") return 1;
    if (type == "AND" || type == "OR" || type == "NAND" || 
        type == "NOR" || type == "XOR" || type == "XNOR") return 2;
    return -1;  // Invalid gate type
}

/**
 * @brief Prints program header and information
 */
void printHeader() {
    cout << "=========================================\n";
    cout << "    Digital Circuit Simulator v1.0\n";
    cout << "         Author: Piyush\n";
    cout << "=========================================\n";
    cout << "\nSupported Gates:\n";
    cout << "  • AND  - Logical AND (2 inputs)\n";
    cout << "  • OR   - Logical OR (2 inputs)\n";
    cout << "  • NOT  - Logical NOT (1 input)\n";
    cout << "  • NAND - NOT AND (2 inputs)\n";
    cout << "  • NOR  - NOT OR (2 inputs)\n";
    cout << "  • XOR  - Exclusive OR (2 inputs)\n";
    cout << "  • XNOR - NOT XOR (2 inputs)\n\n";
}

/**
 * @brief Main program function
 * @return Exit status (0 for success)
 */
int main() {
    printHeader();
    
    // Circuit name input
    string circuitName;
    cout << "Enter circuit name: ";
    getline(cin, circuitName);
    
    if (circuitName.empty()) {
        circuitName = "MyCircuit";
        cout << "Using default name: " << circuitName << "\n";
    }

    // Primary inputs definition
    int nInputs;
    cout << "\nEnter number of primary inputs: ";
    cin >> nInputs;
    
    if (nInputs <= 0) {
        cout << "Error: Circuit must have at least one input.\n";
        return 1;
    }
    
    cout << "Enter names of primary inputs:\n";
    for (int i = 0; i < nInputs; i++) {
        string input;
        cout << "  Input " << (i + 1) << ": ";
        cin >> input;
        primaryInputs.insert(input);
    }

    // Primary outputs definition
    int nOutputs;
    cout << "\nEnter number of primary outputs: ";
    cin >> nOutputs;
    
    if (nOutputs <= 0) {
        cout << "Error: Circuit must have at least one output.\n";
        return 1;
    }
    
    cout << "Enter names of primary outputs:\n";
    for (int i = 0; i < nOutputs; i++) {
        string output;
        cout << "  Output " << (i + 1) << ": ";
        cin >> output;
        primaryOutputs.insert(output);
    }

    // Gate definition phase
    cout << "\n" << string(50, '=') << "\n";
    cout << "GATE DEFINITION PHASE\n";
    cout << string(50, '=') << "\n";
    cout << "Enter gates one by one. Format: TYPE OUTPUT INPUT1 [INPUT2]\n";
    cout << "Examples:\n";
    cout << "  AND Z A B    (Z = A AND B)\n";
    cout << "  NOT Y X      (Y = NOT X)\n";
    cout << "  OR W C D     (W = C OR D)\n";
    cout << "\nType 'END' to finish gate definition.\n\n";
    
    cin.ignore(); // Clear input buffer
    
    int gateCount = 0;
    while (true) {
        string line;
        cout << "Gate " << (gateCount + 1) << ": ";
        getline(cin, line);
        
        // Skip empty lines
        if (line.empty()) continue;
        
        // Parse input line
        stringstream ss(line);
        string type;
        ss >> type;
        type = toUpper(type);
        
        // Check for end condition
        if (type == "END") break;
        
        // Validate gate type
        if (!isValidGateType(type)) {
            cout << "❌ Error: Unknown gate type '" << type << "'.\n";
            cout << "   Supported types: AND, OR, NOT, NAND, NOR, XOR, XNOR\n";
            continue;
        }
        
        // Parse gate definition
        Gate g;
        g.type = type;
        ss >> g.out;
        
        if (g.out.empty()) {
            cout << "❌ Error: Output name required.\n";
            continue;
        }
        
        // Parse inputs
        string input;
        while (ss >> input) {
            g.inputs.push_back(input);
        }
        
        // Validate input count
        int requiredInputs = getRequiredInputs(type);
        if (static_cast<int>(g.inputs.size()) != requiredInputs) {
            cout << "❌ Error: " << type << " gate requires exactly " 
                 << requiredInputs << " input(s), got " << g.inputs.size() << ".\n";
            continue;
        }
        
        // Add gate to circuit
        gates.push_back(g);
        gateCount++;
        
        cout << "✅ Added gate: " << g.type << " " << g.out;
        for (const auto& inp : g.inputs) {
            cout << " " << inp;
        }
        cout << "\n";
    }

    // Check if any gates were defined
    if (gates.empty()) {
        cout << "❌ No gates defined. Cannot simulate empty circuit.\n";
        return 1;
    }

    // Circuit summary
    cout << "\n" << string(50, '=') << "\n";
    cout << "CIRCUIT SUMMARY\n";
    cout << string(50, '=') << "\n";
    cout << "Circuit Name: " << circuitName << "\n";
    cout << "Total Gates: " << gates.size() << "\n";
    cout << "Primary Inputs (" << primaryInputs.size() << "): ";
    for (const auto& inp : primaryInputs) {
        cout << inp << " ";
    }
    cout << "\nPrimary Outputs (" << primaryOutputs.size() << "): ";
    for (const auto& out : primaryOutputs) {
        cout << out << " ";
    }
    cout << "\n\n";
    
    // Generate circuit diagram
    cout << "Generating circuit visualization...\n";
    writeDot(circuitName);

    // Simulation phase
    cout << "\n" << string(50, '=') << "\n";
    cout << "CIRCUIT SIMULATION\n";
    cout << string(50, '=') << "\n";
    
    while (true) {
        cout << "\nEnter values for primary inputs (space-separated):\n";
        cout << "Format: ";
        for (const auto& inp : primaryInputs) {
            cout << inp << " ";
        }
        cout << "\nInput (or 'EXIT' to quit): ";
        
        string inputLine;
        getline(cin, inputLine);
        
        // Check for exit condition
        if (toUpper(inputLine) == "EXIT") break;
        
        // Parse input values
        stringstream inputStream(inputLine);
        values.clear();
        
        bool validInput = true;
        auto it = primaryInputs.begin();
        string valueStr;
        
        // Read input values
        while (it != primaryInputs.end() && inputStream >> valueStr) {
            try {
                int val = stoi(valueStr);
                if (val != 0 && val != 1) {
                    cout << "❌ Error: Input values must be 0 or 1.\n";
                    validInput = false;
                    break;
                }
                values[*it] = val;
                ++it;
            } catch (const exception& e) {
                cout << "❌ Error: Invalid input value '" << valueStr << "'.\n";
                validInput = false;
                break;
            }
        }
        
        // Validate input completeness
        if (validInput && it != primaryInputs.end()) {
            cout << "❌ Error: Not enough input values provided.\n";
            validInput = false;
        }
        
        if (!validInput) {
            cout << "Please try again.\n";
            continue;
        }

        // Simulate circuit
        simulate();

        // Display results
        cout << "\n" << string(40, '-') << "\n";
        cout << "SIMULATION RESULTS\n";
        cout << string(40, '-') << "\n";
        
        cout << "Inputs:\n";
        for (const auto& inp : primaryInputs) {
            cout << "  " << inp << " = " << values[inp] << "\n";
        }
        
        cout << "\nOutputs:\n";
        for (const auto& out : primaryOutputs) {
            if (values.find(out) != values.end()) {
                cout << "  " << out << " = " << values[out] << "\n";
            } else {
                cout << "  " << out << " = undefined\n";
            }
        }
        
        cout << "\nAll Nets:\n";
        for (const auto& p : values) {
            cout << "  " << p.first << " = " << p.second << "\n";
        }
    }

    cout << "\n" << string(50, '=') << "\n";
    cout << "Thank you for using Digital Circuit Simulator!\n";
    cout << string(50, '=') << "\n";
    
    return 0;
}
