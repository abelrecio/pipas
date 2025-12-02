# Pipex

Proyecto de 42 que replica el comportamiento de pipes en shell de Unix.

## Descripción

Pipex ejecuta dos comandos conectados por un pipe, redirigiendo la entrada y salida desde/hacia archivos, simulando el comportamiento de:
```bash
< file1 cmd1 | cmd2 > file2
```

## Compilación
```bash
make        # Compila versión mandatory
make bonus  # Compila versión con bonus (múltiples pipes y heredoc)
make clean  # Limpia archivos objeto
make fclean # Limpia todo
make re     # Recompila desde cero
```

## Uso

### Versión Mandatory
```bash
./pipex file1 cmd1 cmd2 file2
```

**Equivalente a:**
```bash
< file1 cmd1 | cmd2 > file2
```

**Ejemplo:**
```bash
./pipex infile "ls -l" "wc -l" outfile
# Equivale a: < infile ls -l | wc -l > outfile
```

### Versión Bonus

**Múltiples pipes:**
```bash
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```

**Ejemplo:**
```bash
./pipex infile "cat" "grep a" "wc -l" outfile
# Equivale a: < infile cat | grep a | wc -l > outfile
```

**Here_doc:**
```bash
./pipex here_doc LIMITER cmd1 cmd2 file
```

**Equivalente a:**
```bash
cmd1 << LIMITER | cmd2 >> file
```

**Ejemplo:**
```bash
./pipex here_doc EOF "grep hello" "wc -l" outfile
> hello world
> hello 42
> goodbye
> EOF
# Equivale a: grep hello << EOF | wc -l >> outfile
```

## Funcionalidades Bonus

- Soporte para múltiples pipes (n comandos)
- Here_doc con append mode
- Gestión de múltiples procesos hijo
- Manejo de errores robusto

## Estructura del Proyecto
```
pipex/
├── include/
│   └── pipex.h
├── libft/
│   └── [archivos de libft]
├── src_mandatory/
│   ├── main.c
│   ├── command_exec.c
│   ├── command_path.c
│   ├── file.c
│   ├── process.c
│   └── utils.c
├── src_bonus/
│   └── bonus.c
└── Makefile
```

## Gestión de Errores

El programa maneja correctamente:
- Archivos inexistentes o sin permisos
- Comandos no encontrados en PATH
- Errores de fork/pipe
- Sintaxis incorrecta

## Funciones Clave

### Mandatory
- `execute_command()`: ejecuta un comando con execve
- `find_command_path()`: busca el ejecutable en PATH
- `create_pipe()`: crea pipes entre procesos
- `open_input_file()` / `open_output_file()`: maneja archivos

### Bonus
- `handle_multiple_pipes()`: gestiona n pipes
- `handle_heredoc()`: implementa here_doc
- `read_heredoc()`: lee input hasta el LIMITER
- `execute_child()`: configura redirecciones y ejecuta

## Testing
```bash
# Test básico
./pipex infile "cat" "wc -l" outfile

# Test múltiples pipes
./pipex infile "cat" "grep a" "sort" "uniq" outfile

# Test heredoc
./pipex here_doc END "cat" "grep test" outfile

# Comparar con bash
< infile cat | wc -l > expected
./pipex infile "cat" "wc -l" result
diff expected result
```

## Norminette

Código verificado con:
```bash
norminette -R CheckForbiddenSourceHeader
```

## Autor

Proyecto realizado en 42 Madrid

## Notas

- Usa get_next_line para heredoc
- Gestión de memoria sin leaks (verificado con valgrind)
- Maneja señales y status de procesos hijo correctamente

