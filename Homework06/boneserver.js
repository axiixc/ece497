var http = require('http'),
	port = 12344

http.createServer(function (req, res) {
	res.writeHead(200, {'Content-Type': 'text/plain'})
	res.end('Hello World\n')
}).listen(port, '127.0.0.1')

console.log('Server running at http://127.0.0.1:' + port + '/')