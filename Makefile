# Definitions:
hash_func := HashMethod.c  # Hash folding method
rsa_func := RSA.c  # RSA - private and public key generator
program_func := DigitalSign.c  # Digital signature method
program := DigitalSign.o  # Main execution program
signature := signature.rsa  # Signature file
private_key := private.rsa  # Private key file
public_key := public.rsa  # Public key file

# Translate input file name into an program argument:
input_exec_rules := sign auth  # Rules with an input file as argument
exec_rules := build clean genkeys  # Rules without additional inputs

# Check if the given rule is a rule with input file argument:
ifneq ($(filter $(firstword $(MAKECMDGOALS)),$(input_exec_rules)),)
    input := $(filter-out $(input_exec_rules),$(MAKECMDGOALS))
    # Check if there are more (and unnecessary) arguments:
    ifneq ($(word 2,$(input)),) # Then the target has more than one input -> error
        $(error Please provide a single file as input argument)
    endif
    # Check if the given input is another rule:
    ifeq ($(filter $(input),$(exec_rules)),)
        $(eval $(input):;@:) # Make it a non-target input
    else
        # Then the input is a rule (cannot happen) -> error  
        space := $() $()
        comma := , 
        $(error ERROR - Cannot define input file name to be any of the following: \
        $(subst $(space),$(comma),$(input_exec_rules)).)
    endif
else
    # Check if the rule does not require any other inputs:
    ifeq ($(filter $(firstword $(MAKECMDGOALS)),$(exec_rules)),)
        $(error ERROR - Invalid target)
    else
        ifneq ($(words $(MAKECMDGOALS)), 1)
        # Then there is another input (but is unnecessary) -> warn and continue
        $(warning WARNING - No arguments are needed to be supplied with \
        '$(firstword $(MAKECMDGOALS))' target.)
        # Make other arguments non-target arguments:
        $(eval $(filter-out $(exec_rules),$(MAKECMDGOALS)):;@:)
        endif
    endif
endif

# Make rules:	
build:
	gcc $(program_func) $(rsa_func) $(hash_func) -o $(program) -lm
	chmod 777 $(program)

clean:
	rm -f $(program)

genkeys:
	./$(program) genkeys $(private_key) $(public_key)

sign:
	./$(program) sign $(input) $(signature) $(private_key)

auth:
	./$(program) authenticate $(input) $(signature) $(public_key)

