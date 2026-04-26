use BlockDist;

config const n : int = 100000;

var nspace = {1..n}; // range
var d = nspace dmapped Block(nspace); // domain
var a : [d] int; // block distributed array
var x : atomic int; // atomic sum variable

proc main() {
	forall i in d do x.add(a[i]);
}
