package main

import (
    "fmt"
    "net/http"
)

func index( w http.ResponseWriter, req *http.Request) {
    fmt.Fprintf(w, "Hello, world.\n")
}

func main() {
    http.HandleFunc("/", index)
    fmt.Println("listening...")
    err := http.ListenAndServe("127.0.0.1:9999", nil)
    if err != nil {
        panic(err)
    }
}
