# LPYP - Command Line Argument Parser for C

A command line argument parser for C with GNU-style help formatting, built using only libft functions.

## Quick Start

### 1. Define Your Options

```c
t_lpyp_options options[] = {
    {'v', "verbose", 'v', LPYP_NO_ARG, "enable verbose output", NULL},
    {'o', "output", 'o', LPYP_REQUIRED_ARG | LPYP_DENY_DUPLICATE, "place the output into FILE", "FILE"},
    {'O', NULL, 'O', LPYP_OPTIONAL_ARG, "optimize code (level 0-3)", "LEVEL"},
    {0, "color", 200, LPYP_OPTIONAL_ARG, "colorize output", "WHEN"},
    {0, "debug", 201, LPYP_NO_ARG, "enable debug mode", NULL},
    {'h', "help", 'h', LPYP_NO_ARG, "give this help list", NULL},
    {0, "usage", 202, LPYP_NO_ARG, "give a short usage message", NULL},
    {0, NULL, LPYP_KEY_ARG, 0, NULL, "FILES..."},
    {0, NULL, 0, 0, NULL, NULL} /* Sentinel */
};
```

### 2. Create a Parser Function

```c
int my_parser(unsigned int key, void *data, char *argument)
{
    switch (key)
    {
        case 'v':
            ((my_data_t*)data)->verbose = 1;
            break;
        case 'o':
            ((my_data_t*)data)->output_file = argument;
            break;
        case 'O':
            ((my_data_t*)data)->optimization = argument ? ft_atoi(argument) : 2;
            break;
        case 200: /* --color */
            ((my_data_t*)data)->color = argument ? argument : "auto";
            break;
        case 201: /* --debug */
            ((my_data_t*)data)->debug = 1;
            break;
        case 'h':
            lpyp_help(options, argv[0], "Example program demonstrating LPYP.");
            exit(0);
        case 202: /* --usage */
            lpyp_usage(options, argv[0]);
            exit(0);
        case LPYP_KEY_ARG:
            /* Handle non-option arguments (FILES...) */
            add_file_to_list(data, argument);
            break;
        case LPYP_KEY_END:
            /* Parsing finished */
            break;
        default:
            return (1); /* Error */
    }
    return (0);
}
```

### 3. Parse Arguments

```c
my_data_t data = {0};
if (lpyp_parse(&data, argc, argv, options, my_parser) != 0)
{
    lpyp_usage(options, argv[0]);
    return (1);
}
```

## API Reference

### Structures

#### `t_lpyp_options`

```c
typedef struct s_lpyp_options
{
    char            short_name;     /* Single character option (-v) */
    char            *long_name;     /* Long option name (--verbose) */
    unsigned int    key;            /* Unique identifier */
    int             flags;          /* Option behavior flags */
    char            *description;   /* Help text description */
    char            *arg_name;      /* Argument name for help (e.g., "FILE") */
}   t_lpyp_options;
```

### Flags

- `LPYP_NO_ARG`: Option takes no argument
- `LPYP_REQUIRED_ARG`: Option requires an argument
- `LPYP_OPTIONAL_ARG`: Option has an optional argument
- `LPYP_DENY_DUPLICATE`: Option cannot appear multiple times
- `LPYP_SEEN`: Internal flag indicating option has been seen (automatically managed)

### Special Keys

- `LPYP_KEY_ARG`: Non-option argument encountered
- `LPYP_KEY_END`: End of argument parsing
- `LPYP_KEY_UNKNOWN`: Unknown option encountered

### Functions

#### `lpyp_parse`

```c
int lpyp_parse(void *data, int argc, char **argv, t_lpyp_options *options, t_lpyp_parser parser_func);
```

Main parsing function. Returns 0 on success, 1 on error.

#### `lpyp_help`

```c
int lpyp_help(t_lpyp_options *options, char *program_name, char *description);
```

Prints detailed help information in professional GNU-style format, including:
- Complete usage line with all options in bracket notation
- Program description
- Properly aligned option list with descriptions
- Support for all option types (short, long, long-only, with/without arguments)

#### `lpyp_usage`

```c
int lpyp_usage(t_lpyp_options *options, char *program_name);
```

Prints concise usage information in GNU-style format showing all options in compact bracket notation. Perfect for error messages and quick reference.

#### `lpyp_reset_options`

```c
void lpyp_reset_options(t_lpyp_options *options);
```

Resets the internal seen flags for all options, allowing the same options array to be reused for multiple parsing sessions. This function clears the `LPYP_SEEN` flags that track duplicate options when `LPYP_DENY_DUPLICATE` is used.

## Help and Usage Output Examples

### Help Output (`./program --help`)

```
Usage: ./program [-v] [-o FILE] [-O[ LEVEL]] [--color[=WHEN]] [--debug] [-h] [--usage] FILES...

Example program demonstrating LPYP.

Options:
  -v, --verbose      enable verbose output
  -o, --output FILE  place the output into FILE
  -O [LEVEL]         optimize code (level 0-3)
      --color[=WHEN] colorize output
      --debug        enable debug mode
  -h, --help         give this help list
      --usage        give a short usage message
```

### Usage Output (`./program --usage`)

```
Usage: ./program [-v] [-o FILE] [-O[ LEVEL]] [--color[=WHEN]] [--debug] [-h] [--usage] FILES...
```

## Examples

### Basic Usage

```bash
./program -v --output=results.txt input.txt
./program -vh -o results.txt input.txt  
./program --verbose --help
./program -O2 --color=always file1.c file2.c
./program --debug --color file.txt
```

### Option Types

```bash
# Short options with arguments
./program -o output.txt -O3

# Long options with arguments  
./program --output=output.txt --color=never

# Long-only options
./program --debug --usage

# Optional arguments
./program -O            # Uses default optimization level
./program -O2           # Uses optimization level 2
./program --color       # Uses default color setting
./program --color=auto  # Uses specific color setting
```

### Duplicate Option Control

```bash
# Options without LPYP_DENY_DUPLICATE can be repeated
./program -v -v --verbose          # Works - multiple verbose flags

# Options with LPYP_DENY_DUPLICATE cannot be repeated  
./program --output=file1 --output=file2  # Error: option already specified
./program -d --debug                     # Error: option already specified
```

### Error Handling

```bash
./program -o              # Error: missing required argument
./program --unknown       # Error: unrecognized option
./program -x              # Error: invalid option
```

### Special Cases

```bash
./program file.txt -- --not-an-option    # Everything after -- treated as arguments
./program --help                         # Show help
./program                                # Show usage
```

### Reusing Options Array

If you need to parse arguments multiple times with the same options array (e.g., in interactive programs or testing), use `lpyp_reset_options` to clear the internal state:

```c
t_lpyp_options options[] = {
    {'o', "output", 'o', LPYP_REQUIRED_ARG | LPYP_DENY_DUPLICATE, "output file", "FILE"},
    {0, NULL, 0, 0, NULL, NULL} /* Sentinel */
};

// First parsing session
my_data_t data1 = {0};
lpyp_parse(&data1, argc1, argv1, options, my_parser);

// Reset for reuse
lpyp_reset_options(options);

// Second parsing session (works even with LPYP_DENY_DUPLICATE options)
my_data_t data2 = {0};
lpyp_parse(&data2, argc2, argv2, options, my_parser);
```

## Building

```bash
make all     # Build library only
make clean   # Clean object files
make fclean  # Clean everything
```
