Description:
Program where you can see how long it takes to pay of mortage with normal monthly
payments and abnormal payments here and there



Was Developed using Qt

To deploy:
1. Have exe complied and txt files
2. Open console
3. run
4. change directory to qt bin folder version that you are using
5. run qtenv2.bat
6. run windeployqt.exe
7. run windeployqt.exe --quick --no-translations

Key Notes:
-Any line with # will not be read in
-Main Data Must be in order of:
    1. Mortage Amount - dollars with no commas
    2. Yearly Interest Rate - 0 - 100% per year
    3. Normal Monnthly Payment - dollars with no commas
    4. Abnormal Monthly Payments - YYYY MM Money
        4a. YYYY is years with 4 digits like 0000 - 9999
        4b. MM is months ranging from 01 - 12
        4c. Money is any digit ranging from 0.00 - 99999999999.00
- Any Date that is ealier than the current date is not a valid date and will not be considered
- The Dates can be in any order
- The File must be called "InputData.txt" in the directory




Under this is an example Templete


# Mortgage Amount($):
200000.32
# Yearly Interest Rate(%):
3.2
# Normal Monthly Payment:
2123.00
# Abnorrmal Payments(Seperated by One Space):
# Year Month Amount
#----------------------------------------------------
2020 10 5000
2021 01 2000
2022 03 20000
2020 03 2000
2020 03 6000
1999 01 10000
