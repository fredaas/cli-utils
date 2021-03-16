#!/usr/bin/env bash

open-pdf()
{
    evince $1 &>/dev/null &
}

alias git-list-tracked="git ls-tree -r master --name-only"
alias print-path="tr ':' '\n' <<< $PATH"
alias print-man="man -k . s"
alias pdfopen="open-pdf"
