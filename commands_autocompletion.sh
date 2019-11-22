# file: commands.sh

_commands ()
{
  local cur
  # Pointer to current completion word.
  # By convention, it's named "cur" but this isn't strictly necessary.

  COMPREPLY=()   # Array variable storing the possible completions.
  cur=${COMP_WORDS[COMP_CWORD]}

  case "$cur" in
    -*)
    COMPREPLY=( $( compgen -W '--make_parameterization --make_error_plots --make_optical_functions_plot' -- $cur ) );
  esac

  return 0
}

complete -o default -o bashdefault -o filenames -F _commands  ./commands.sh