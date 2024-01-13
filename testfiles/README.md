# testfiles

This is a folder where tests should be placed in order to be executed.

Accepted test format:

TAR archive (XX-0000.tar) containing two files:
* Test information (naming convention: XX-0000.info)
* Binary file used for testing (naming convention: XX-0000)

## .info file

Information file contains information about the test in order:
* 1st line - #TEST# - test info file signature,
* 2nd line - test ID (same as in filename),
* 3rd line - cyberattack type,
* 4th line - brief test description, unused in current version of the environment.

## binary file

All performed tests should meet all these HRI criteria:
* Harmless - the purpose of the test should be discovering vulnerabilities, not exploiting them! Tests should only mimic threat, not pose a security risk to the system!
* Reversible - tests and all changes that were made during their runtime should be easily reversible!
* Invisible (outside of test cases) - make sure all created tests will not be removed before they even begin!

Example test has been presented in EX-1234 and contains a simple, harmless program which should not be detected by any compatible antivirus software.

Other tests present different cases of data - invalid format, invalid signature, invalid ID etc. Their characteristics and expected result can be found inside their designated .info file (if present)

#

DISCLAIMER: author cannot be held responsible when these files or your AV scanner in combination with these files cause any damage to your computer. YOU DOWNLOAD THESE FILES AT YOUR OWN RISK. Download these files only if you are sufficiently secure in the usage of your AV scanner.
