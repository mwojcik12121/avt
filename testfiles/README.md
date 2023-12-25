# testfiles

This is a folder where tests should be placed.

Accepted test format:

TAR archive (XX-0000.tar) containing two files:
* Test information (naming convention: XX-0000.info)
* Binary file used for testing (naming convention: XX-0000)

## .info file

Information file contains information about the test in order:
* 1st line - #TEST# - test info file signature,
* 2nd line - cyberattack type,
* 3rd line - brief test description, unused in current version of the environment.

Example test has been presented in EX-1234 and contains basic "Hello World!" program.