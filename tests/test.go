// Example Go file for source-highlight.

package main

import "fmt"

func main() {
	var words = []string{"foo", "bar", "baz"}
	greeting := `Hello`
	for _, word := range words {
		fmt.Printf("%s, %s!\n", greeting, word)
	}
}
