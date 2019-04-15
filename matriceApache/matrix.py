import sys

def read_file(file):
    with open(file, 'r') as gtf_file:
        gtf_file_lines = gtf_file.readlines()
    return gtf_file_lines
file = read_file(sys.argv[1])

matrix=file[14:]

print(matrix[-1])
