SIMULATION_TIME='57'
TASKS_NUM='5'
M='2'
K='5'
NUMBER='4'

def read_task_file(filename):
    with open(filename, 'r') as file:
        data = file.read()
    
    # Remove unwanted characters
    data = data.strip('{}').replace('False', 'false').replace('True', 'true')
    
    # Split data into lines and remove empty lines
    lines = [line.strip() for line in data.split('\n') if line.strip()]
    
    return lines

def generate_c_code(lines):
    tasks_initialization = "Task tasks[TASKS_NUM] = {\n"
    for line in lines:
        tasks_initialization += f"    {line}\n"
    
    return tasks_initialization

def write_c_file(filename, c_code):
    with open(filename, 'w') as file:
        file.write("// task.h\n")
        file.write("#ifndef TASK_H\n#define TASK_H\n\n")
        file.write("#include <stdbool.h>\n\n")
        file.write("#define SIMULATION_TIME "+SIMULATION_TIME+"\n")
        file.write("#define TASKS_NUM "+TASKS_NUM+"\n")
        file.write("#define M "+M+"\n")
        file.write("#define K "+K+"\n")
        file.write("#define NUMBER "+NUMBER+"\n\n")
        file.write("typedef struct {\n")
        file.write("    int id;\n")
        file.write("    int wcet;\n")
        file.write("    int period;\n")
        file.write("    int deadline;\n")
        file.write("    bool schedulable;\n")
        file.write("    int remaining;\n")
        file.write("    int nextStart;\n")
        file.write("    int activation;\n")
        file.write("    int abDeadline;\n")
        file.write("    int count;\n")
        file.write("    bool flag;\n")
        file.write("} Task;\n\n")
        file.write("extern Task tasks[TASKS_NUM];\n\n")
        file.write(c_code)
        file.write("\n")
        file.write("void init();\n\n")
        file.write("#endif\n\n")
        

def main():
    txt_filename = "taskset.txt"
    c_filename = "task.h"
    
    # Read task data from txt file
    lines = read_task_file(txt_filename)
    
    # Generate C code for task initialization
    c_code = generate_c_code(lines)
    
    # Write the C code to the task.h file
    write_c_file(c_filename, c_code)

if __name__ == "__main__":
    main()
