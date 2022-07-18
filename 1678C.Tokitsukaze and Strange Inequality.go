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

	p := make([]int, n)
	// cnt[i][j]前i个位置中，小于j的个数
	cnt := make([][]int64, n)

	for i := range p {
		Fscan(in, &p[i])
		p[i]--
		cnt[i] = make([]int64, n)
		for j := range cnt[i] {
			cnt[i][j] = 0
			if i > 0 {
				cnt[i][j] = cnt[i-1][j]
			}

			if p[i] < j {
				cnt[i][j]++
			}
		}
	}
	var ans int64 = 0
	for b := 1; b < n-2; b++ {
		for c := b + 1; c < n-1; c++ {
			ans += cnt[b-1][p[c]] * (cnt[n-1][p[b]] - cnt[c][p[b]])
		}
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
