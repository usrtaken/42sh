# 42sh

You must write a Unix SHELL.

The project has two sections :

• a mandatory section, which MUST be completed: display a prompt, parse and execute some commands (see below),

• an optional section, which will only be evaluated if the mandatory section is fully functionnal.
Authorized functions: all functions included in the libC or the ncurses library.


MANDATORY

This section must be COMPLETELY FUNCTIONAL. Otherwise your grade will be 0.

Concerning command parsing and execution, you must handle:

•spaces and tabs,

•$PATH and environment,

•errors and return value,

•redirections (‘<’, ‘>’, ‘<<’ and ‘>>’),

•pipes (‘|’),

•builtins: cd, echo, exit, setenv, unsetenv,

•separators: ‘;’, ‘&&’, ‘||’.


OPTIONAL


•inhibitors (‘\’),

•globbings (‘*’, ‘?’, ‘[’, ’]’),

•job control (‘&’, fg),

•backticks (“’),

•parentheses (‘(’ and ‘)’),

•variables (local and env),

•special variables (term, precmd, cwdcmd, cwd, ignoreof for instance),

•history (‘!’),

•aliases,

•line edition (multiline, dynamic rebinding, auto-completion dynamic,

•scripting (a bit harsh though).


What is missing


• Inhibitors (working with only one space after '')

• Job Control

• Parentheses

• History (working with arrows but not with '!')

• For each
