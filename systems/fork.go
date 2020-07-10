package main

import (
	"fmt"
	"syscall"
)

func main() {
	prog := "/bin/ls"
	args := []string{"/bin/ls", "-al"}
	pid, err := syscall.ForkExec(prog, args, nil)
	if err != nil {
		fmt.Printf("Error = %v\n", err)
		return
	}
	fmt.Println(pid)
}
