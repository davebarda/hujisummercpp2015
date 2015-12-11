__author__ = 'davebarda'

from random import randint
from random import uniform
import os
from sys import argv

def main(argv):
    if not(os.path.exists(os.path.abspath(os.curdir) + "/Tests/")):
        os.mkdir(os.path.abspath(os.curdir) + "/Tests/")
    for i in range(0, int(argv[0])):
        operation = randint(1, 4)
        f = open(os.path.abspath(os.curdir) + "/Tests/int_" + str(operation)
                 + "_" + str(i), "w+")
        num_of_rows_first = randint(0, 500)
        num_of_cols_first = num_of_rows_first + randint(0, 1)
        f.write(str(1) + "\n")
        f.write(str(operation) + "\n")
        f.write(str(num_of_rows_first) + "\n")
        f.write(str(num_of_cols_first) + "\n")
        for j in range(0, num_of_rows_first):
            for k in range(0, num_of_cols_first):
                f.write(str(randint(0, 9999)))
                f.write(',')
            f.write("\n")
        if operation <= 2:
            num_of_rows_second = num_of_rows_first + randint(0, 1)
            num_of_cols_second = num_of_cols_first + randint(0, 1)
            f.write(str(num_of_rows_second) + "\n")
            f.write(str(num_of_cols_second) + "\n")
            for j in range(0, num_of_rows_second):
                for k in range(0, num_of_cols_second):
                    f.write(str(randint(0, 9999)))
                    f.write(',')
                f.write("\n")

    for i in range(0, int(argv[1])):
        operation = randint(1, 4)
        f = open(os.path.abspath(os.curdir) + "/Tests/double_" + str(operation)
                 + "_" + str(i), "w+")
        num_of_rows_first = randint(0, 500)
        num_of_cols_first = num_of_rows_first + randint(0, 1)
        f.write(str(2) + "\n")
        f.write(str(operation) + "\n")
        f.write(str(num_of_rows_first) + "\n")
        f.write(str(num_of_cols_first) + "\n")
        for j in range(0, num_of_rows_first):
            for k in range(0, num_of_cols_first):
                f.write(str(uniform(0, 9999)))
                f.write(',')
            f.write("\n")
        if operation <= 2:
            num_of_rows_second = num_of_rows_first + randint(0, 1)
            num_of_cols_second = num_of_cols_first + randint(0, 1)
            f.write(str(num_of_rows_second) + "\n")
            f.write(str(num_of_cols_second) + "\n")
            for j in range(0, num_of_rows_second):
                for k in range(0, num_of_cols_second):
                    f.write(str(uniform(0, 9999)))
                    f.write(',')
                f.write("\n")

    for i in range(0, int(argv[2])):
        operation = randint(1, 4)
        f = open(os.path.abspath(os.curdir) + "/Tests/complex_" + str(operation)
                 + "_" + str(i), "w+")
        num_of_rows_first = randint(0, 500)
        num_of_cols_first = num_of_rows_first + randint(0, 1)
        f.write(str(3) + "\n")
        f.write(str(operation) + "\n")
        f.write(str(num_of_rows_first) + "\n")
        f.write(str(num_of_cols_first) + "\n")
        for j in range(0, num_of_rows_first):
            for k in range(0, num_of_cols_first):
                f.write(str(uniform(0, 9999)) + "+" + str(uniform(0, 9999)) + "i")
                f.write(',')
            f.write("\n")
        if operation <= 2:
            num_of_rows_second = num_of_rows_first + randint(0, 1)
            num_of_cols_second = num_of_cols_first + randint(0, 1)
            f.write(str(num_of_rows_second) + "\n")
            f.write(str(num_of_cols_second) + "\n")
            for j in range(0, num_of_rows_second):
                for k in range(0, num_of_cols_second):
                    f.write(str(uniform(0, 9999)) + "+" + str(uniform(0, 9999)) + "i")
                    f.write(',')
                f.write("\n")

if __name__ == '__main__':
    main(argv[1:])
