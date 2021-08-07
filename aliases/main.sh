macro::pdfopen()
{
    evince $1 &>/dev/null &
}

alias git-list-tracked="git ls-tree -r HEAD --name-only"
alias print-path="tr ':' '\n' <<< $PATH"
alias print-man="man -k . s"
alias pdfopen=macro:pdfopen
