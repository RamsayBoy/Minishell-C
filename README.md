# Minishell-C
## Installation
### ATTENTION
For now, it is a little mess but I will find out better ways of doing it (and it will be all automatic).

### Requirements
Those versions were used during development:
- GNU make 4.2.1
- gcc 9.2.1

If you want to use another version, is up to you.

### Building the minishell
1. Clone this repository:
```
git clone https://github.com/RamsayBoy/Minishell-C.git
```
2. Go into the root directory:
```
cd Minishell-C
```
3. Run the following command:
```
make create_dirs && make
```

### Running the minishell
After building the minishell, go into "bin" directory and run ```./minishell```.

### Cleaning files
For cleaning, just execute ```make clean```.
