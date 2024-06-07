# Project Assignment Phase 4 and 5

## Installation

To install the project, simply run:

```sh
make
```

## Testing Phase 4

To test the implementation for Phase 4, execute the following command:

```sh
./parser example
```

### Known Issues in Phase 4

- **Incorrect Values**: The parser does not always return correct values.
- **Type Inconsistencies**: There are occasional issues with type recognition.
- **Offset Problems**: We encountered a problem with the offset calculation which affects the parsing results.

## Phase 5 Implementation

Given the limited time remaining, we started implementing the necessary tools for Phase 5. However, due to time constraints, we were unable to complete all the required functionalities.

### Tools Implemented

- `avm_table`
- `execute`
- `libfunc`
- `avm`

### Tools Not Implemented

The following tools and functionalities were not implemented:

- AvmTable operations:
  - `avm_getable`
- Execute operations:
  - `jne` (Jump if not equal)
  - `jle` (Jump if less or equal)
  - `jge` (Jump if greater or equal)
  - `jlt` (Jump if less than)
  - `jgt` (Jump if greater than)
  - `uminus` (Unary minus)
  - `and`
  - `or`
  - `not`
- Functions to read the binary file.
- The main function needed to test Phase 5.

### Test Functions

Despite the incomplete implementation, test functions were written for most of the tools to ensure they work as intended. These tests can be found in the `avm` directory and can be executed to verify the functionalities that have been implemented.

## Conclusion

While we faced several challenges and time constraints, significant progress was made in implementing and testing the core functionalities of the project. 

---

Thank you for reviewing our submission. If there are any questions or further clarifications needed, please do not hesitate to reach out.

**Project Team:**
**Iason Karatarakis csd4536,**
**Nikos Dritsas csd3941**