package main

import (
	"bufio"
	. "fmt"
	"io"
	"os"
)

func solve(in io.Reader, out io.Writer) {
	var n int
	Fscan(in, &n)

	mp := make(map[int]bool)

	var a int
	zeroCnt := 0
	dup := false
	for i := 0; i < n; i++ {
		Fscan(in, &a)

		if a == 0 {
			zeroCnt++
		}

		_, ok := mp[a]
		if ok {
			dup = true
		} else {
			mp[a] = true
		}
	}

	var ans int
	if zeroCnt != 0 {
		ans = n - zeroCnt
	} else if dup {
		ans = n
	} else {
		ans = n + 1
	}
	Fprintln(out, ans)

}

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()
	var T int
	for Fscan(in, &T); T > 0; T-- {
		solve(in, out)
	}
}
