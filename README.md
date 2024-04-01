# Question-Answer Program

This C++ program is designed to extract answers to given questions from a script. It finds answers by utilizing similarities between the given script file and the question file.

## How to Use

1. Create two text files named `script.txt` and `questions.txt`.
2. Write the script in the `script.txt` file and the questions in the `questions.txt` file.
3. Run the program and enter the name of the script file and the question file.
4. The program will print the answers it finds for each question.

## Requirements

- C++ compiler
- Header files: `iostream`, `fstream`, `string`, `ctime`, `cstdlib`

## Example Usage

Enter the name of the script's file(.txt): script.txt
Enter the name of the question's file(.txt): questions.txt

The program will print the answers it finds in the script for each question.

## Notes

- The program assumes that the script and question files are in the appropriate format.
- If the files are not suitable, the program may encounter errors.
- Ensure that the script and question files are in UTF-8 format.
- The clarity and precision of the given questions may affect the accuracy of the answers found.
