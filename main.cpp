/* ========================================================================== */
/*                                                                            */
/*    ██╗  ██╗██████╗   █████╗ ██╗   ██╗                                      */
/*    ██║  ██║╚════██╗ ██╔══██╗██║   ██║                                      */
/*    ███████║ █████╔╝ ███████║██║   ██║       by: mpillet                    */
/*    ╚════██║██╔═══╝  ██╔══██║╚██╗ ██╔╝       at: 2015/02/12 12:34:46        */
/*         ██║███████╗ ██║  ██║ ╚████╔╝                                       */
/*         ╚═╝╚══════╝ ╚═╝  ╚═╝  ╚═══╝                                        */
/*                                                                            */
/* ========================================================================== */

#include "Vm.hpp"
#include "Parser.hpp"
#include "avm.hpp"

#include <iostream>

int usage (char * name)
{
	std::cout << "usage: " << name << " [file]" << std::endl;
	return (1);
}

void display_err (std::string type, std::exception & e)
{
	std::cout << type << ": " << "Line " << Vm::single().getLine() << ": " << e.what() << std::endl;
}

int main (int ac, char ** av)
{
	Vm 		vm = Vm::single();
	Parser	parser;

	if (ac > 2) {
		return usage(av[0]);
	}

	try {

		if (ac == 1) {
			parser.parseFromStdin();
		} else {
			parser.parseFromFile(av[1]);
		}

		vm.execute();

	}
	catch (SyntaxException & e)    { display_err("Syntax Error",    e); }
	catch (ExecutionException & e) { display_err("Execution Error", e); }
	catch (std::exception & e)     { display_err("Unknown Error",   e); }

	return (0);
}
