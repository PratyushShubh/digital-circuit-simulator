# Contributing to Digital Circuit Simulator

Thank you for your interest in contributing to the Digital Circuit Simulator! This document provides guidelines and information for contributors.

## 🤝 How to Contribute

### Reporting Issues
- **Search existing issues** first to avoid duplicates
- **Use the issue template** when available
- **Provide detailed information**:
  - Operating system and version
  - Compiler version
  - Steps to reproduce the issue
  - Expected vs actual behavior
  - Error messages (if any)

### Suggesting Features
- Check if the feature has been requested before
- Explain the use case and benefits
- Consider backwards compatibility
- Provide implementation ideas if possible

### Code Contributions

#### Getting Started
1. **Fork the repository** on GitHub
2. **Clone your fork** locally:
   ```bash
   git clone https://github.com/your-username/circuit-simulator.git
   cd circuit-simulator
   ```
3. **Create a feature branch**:
   ```bash
   git checkout -b feature/your-feature-name
   ```

#### Development Setup
1. **Install dependencies**:
   - C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
   - Optional: Graphviz for visualization testing

2. **Build the project**:
   ```bash
   # Using Makefile (recommended)
   make all
   
   # Or manually
   g++ -o circuit circuit.cpp -std=c++17 -Wall -Wextra
   ```

3. **Test your changes**:
   ```bash
   make test
   ./circuit.exe  # Run manual tests
   ```

## 📋 Code Style Guidelines

### General Principles
- **Clarity over cleverness**: Write code that's easy to read and understand
- **Consistency**: Follow existing patterns in the codebase
- **Documentation**: Comment complex logic and public interfaces

### Formatting
- **Indentation**: 4 spaces (no tabs)
- **Braces**: Opening brace on same line
- **Line length**: Maximum 100 characters
- **Naming conventions**:
  - Variables: `camelCase`
  - Functions: `camelCase()`
  - Classes/Structs: `PascalCase`
  - Constants: `UPPER_CASE`

### Example Code Style
```cpp
/**
 * @brief Brief description of the function
 * @param param1 Description of parameter
 * @return Description of return value
 */
int calculateGateOutput(const Gate& gate, const InputValues& inputs) {
    if (gate.type == "AND") {
        return inputs[gate.inputs[0]] & inputs[gate.inputs[1]];
    }
    
    // Handle other gate types...
    return 0;
}
```

### Documentation
- Use **Doxygen-style comments** for public functions
- Include **inline comments** for complex logic
- Update **README.md** for new features
- Add **examples** for new functionality

## 🧪 Testing Guidelines

### Writing Tests
- **Test all new features** with various input combinations
- **Include edge cases** and error conditions
- **Create example circuits** that demonstrate functionality
- **Test cross-platform compatibility** when possible

### Test Organization
```
examples/
├── basic_gates/          # Individual gate tests
├── complex_circuits/     # Multi-gate circuit tests
├── error_cases/         # Invalid input tests
└── performance/         # Large circuit tests
```

### Running Tests
```bash
# Run all tests
make test

# Manual testing
./circuit < examples/half_adder_test.txt

# Debug build for testing
make debug
./circuit
```

## 🎯 Priority Areas for Contribution

### High Priority
- **Bug fixes** in core simulation logic
- **Cross-platform compatibility** improvements
- **Performance optimizations** for large circuits
- **Error handling** enhancements

### Medium Priority
- **New gate types** (multiplexer, decoder, etc.)
- **Improved visualization** features
- **Better input validation**
- **Code refactoring** and cleanup

### Low Priority
- **GUI interface** development
- **File format support** (VHDL/Verilog import)
- **Advanced features** (timing analysis, etc.)

## 🔧 Pull Request Process

### Before Submitting
1. **Update documentation** if needed
2. **Add tests** for new functionality
3. **Run existing tests** to ensure nothing breaks
4. **Check code style** compliance
5. **Write clear commit messages**

### Commit Message Format
```
type(scope): brief description

Detailed explanation of changes (if needed)

Fixes #issue-number (if applicable)
```

**Types**: `feat`, `fix`, `docs`, `style`, `refactor`, `test`, `chore`

**Examples**:
```
feat(gates): add multiplexer gate support

- Implement 2:1 and 4:1 multiplexer gates
- Add validation for select inputs
- Include test cases and examples

Fixes #25
```

### Pull Request Template
1. **Description**: What does this PR do?
2. **Testing**: How was it tested?
3. **Breaking Changes**: Any backwards compatibility issues?
4. **Screenshots**: For UI changes (if applicable)

## 🐛 Debugging Guidelines

### Common Issues
1. **Compilation errors**:
   - Check C++17 support
   - Verify include paths
   - Review compiler warnings

2. **Runtime errors**:
   - Use debug build: `make debug`
   - Add logging to trace execution
   - Check memory management

3. **Logic errors**:
   - Test with simple circuits first
   - Verify gate truth tables
   - Check input/output mappings

### Debug Tools
- **GDB**: For step-through debugging
- **Valgrind**: For memory leak detection (Linux/macOS)
- **AddressSanitizer**: Built-in with `-fsanitize=address`

## 📚 Resources

### Learning Resources
- **C++17 Reference**: https://en.cppreference.com/
- **Digital Logic**: Basic concepts and gate behavior
- **Graphviz Documentation**: https://graphviz.org/documentation/

### Development Tools
- **Visual Studio Code**: With C++ extension
- **CLion**: JetBrains C++ IDE
- **Code::Blocks**: Lightweight C++ IDE

## 🏆 Recognition

### Contributors
All contributors are recognized in the project documentation and release notes.

### Types of Contribution
- **Code contributions**: Features, bug fixes, optimizations
- **Documentation**: README updates, code comments, examples
- **Testing**: Bug reports, test cases, platform testing
- **Design**: UI/UX improvements, architecture suggestions

## 📞 Getting Help

### Communication Channels
- **GitHub Issues**: For bugs and feature requests
- **GitHub Discussions**: For questions and general discussion
- **Email**: Direct contact for urgent issues

### Response Times
- **Bug reports**: Within 2-3 days
- **Feature requests**: Within 1 week
- **Pull requests**: Within 1 week

## 📝 License

By contributing to this project, you agree that your contributions will be licensed under the same [MIT License](LICENSE) that covers the project.

---

**Thank you for contributing to Digital Circuit Simulator! 🚀**