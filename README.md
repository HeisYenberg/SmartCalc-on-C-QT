# SmartCalc v1.0

## Implementation of SmartCalc v1.0.

## Usage :

- To install the app run `make install`
- To open app run `make open`
- To see tests run `make test`, might need to install `check`
- To see tests code coverage run `make gcov_report`, might need to install `lcov`

### Overview of "SmartCalc v1.0" functions

| Operator name  | Arithmetic operators | Function description       | Functions |
|----------------|----------------------|----------------------------|-----------|
| Brackets       | (a + b)              | Computes cosine            | cos(x)    |
| Addition       | a + b                | Computes sine              | sin(x)    |
| Subtraction    | a - b                | Computes tangent           | tan(x)    |
| Multiplication | a * b                | Computes arc cosine        | acos(x)   |
| Division       | a / b                | Computes arc sine          | asin(x)   |
| Power          | a ^ b                | Computes arc tangent       | atan(x)   |
| Modulus        | a mod b              | Computes square root       | sqrt(x)   |
| Unary plus     | +a                   | Computes natural logarithm | ln(x)     |
| Unary minus    | -a                   | Computes common logarithm  | log(x)    |

Graph of function:

- Builds a graph of a provided function.

Credit calculator:

- Input: total credit amount, term, interest rate, type (annuity, differentiated)
- Output: monthly payment, overpayment on credit, total payment