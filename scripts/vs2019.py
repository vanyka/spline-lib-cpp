import os

GENERATOR = 'Visual Studio 16 2019'

os.system(f'cmake -G "{GENERATOR}" -S .. -B ../_builds/vs2019')

input("Press Enter to continue...")
