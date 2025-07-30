# python code for calculator
print("Welcome to the Calculator!"
      "\nYou can perform basic arithmetic operations like addition, subtraction, multiplication, and division."
      "\nPlease enter two numbers to perform operations on them."
      "\nType 'exit' to quit the calculator."
      )
print("1. addition \n 2. subtraction \n 3. multiplication \n 4. division")
a = input("Enter first number: ")
b = input("Enter second number: ")
c = input("Enter operation: ")
if c == "1":
    print("The sum of", a, "and", b, "is", float(a) + float(b))
elif c == "2":
    print("The difference between", a, "and", b, "is", float(a) - float(b))
elif c == "3":
    print("The product of", a, "and", b, "is", float(a) * float(b))
elif c == "4":
    if float(b) != 0:
        print("The division of", a, "by", b, "is", float(a) / float(b))
    else:
        print("Error: Division by zero is not allowed.")
else:
    print("Invalid operation selected. Please choose a valid operation (1-4).")

