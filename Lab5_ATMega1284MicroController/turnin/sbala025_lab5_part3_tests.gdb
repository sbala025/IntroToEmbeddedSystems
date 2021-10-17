# Test file for "Lab3_bitManipulation"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
test "PINA: 0x14 => PORTC: 0x70"
setPINA 0x14
continue 2
expectPORTC 0x70
checkResult

test "PINA: 0x00 => PORTB: 0x00"
setPINA 0x00
count = 0;
expectPORTB 0x00
checkResult

test "PINA: 0x01, count = 1 => PORTB: 0x21"
setPINA 0x01
count = 1;
expectPORTB 0x21
checkResult

test "PINA: 0x01, count = 3 => PORTB: 0x0C"
setPINA 0x01
count = 3;
expectPORTB 0x0C
checkResult

test "PINA: 0x01, count = 5 => PORTB: 0x38"
setPINA 0x01
count = 5;
expectPORTB 0x38
checkResult

test "PINA: 0x01, count = 7 => PORTB: 0x3C"
setPINA 0x01
count = 7;
expectPORTB 0x3C
checkResult


# Add tests below

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
