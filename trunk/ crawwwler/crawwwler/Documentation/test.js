function go() {
	this.a = new Array();

}

go.prototype.getIt = function() {
	alert("hello, world!");
	return this.a;
}