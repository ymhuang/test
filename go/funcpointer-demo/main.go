package main

import (
  "fmt"
  "os"
)

type oneStringFuncPointer func(string)
type twoStringFuncPointer func(string, string)

func funcOneString( s string) {
    fmt.Printf("Hello, %s\n", s )
}

func funcTwoString( s1, s2 string) {
    fmt.Printf("%s: %s\n", s1, s2)
}

func main() {
    var fp1 oneStringFuncPointer = funcOneString
    var fp2 twoStringFuncPointer = funcTwoString
    var i int = 0
    var s string = "World."

    if (len(os.Args) <= 1) {
        fp1(s)
    } else {
        for i = 1; i < len(os.Args); i++ {
            s = fmt.Sprintf("%s", os.Args[i])
            fp1(s)
            fp2(fmt.Sprintf("%d", i), s)
        }
    }
}
