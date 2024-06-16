import subprocess
import re

def run_cbmc_with_timing():
    
    command = ['timeout', '1800', 'time', 'cbmc', '--object-bits', '16', '--property', 'main.assertion.1', 'main.c', 'init.c', 'simulate.c']
    
    try:
        # Run the command and capture the output
        result = subprocess.Popen(command, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        stdout, stderr = result.communicate()
        # Print CBMC output
        print("\nCBMC Output:")
        print(stdout)

        # Extract and print timing information
        timing_output = stderr.strip()
        timing_info = re.findall(r"(\d+\.\d+user) (\d+\.\d+system) (\d+:\d+\.\d+elapsed)", timing_output)

        if timing_info:
            user_time, sys_time, elapsed_time = timing_info[0]
            print(f"User time: {user_time}")
            print(f"System time: {sys_time}")
            print(f"Elapsed time: {elapsed_time}")
        
    except subprocess.CalledProcessError as e:
        print(f"CBMC returned non-zero exit status: {e.returncode}")
        print(f"CBMC output:\n{e.output}")
    except subprocess.TimeoutExpired:
        print("CBMC execution timed out.")
    except FileNotFoundError:
        print("Error: 'cbmc' not found. Make sure it is installed and in your PATH.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Main script
if __name__ == "__main__":
    run_cbmc_with_timing()