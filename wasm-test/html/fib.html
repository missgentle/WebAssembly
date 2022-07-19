<!DOCTYPE html>
<html>

<head>
	<title></title>
</head>

<body>
	<script type="text/javascript">
		// JS实现
		function fib(x) {
			if (x < 2) {
				return 1;
			} else {
				return fib(x - 1) + fib(x - 2);
			}
		}
		// 使用performance API测量时间更加稳定和精确
		let JStartTime = performance.now();
		console.log(fib(45));
		console.log(`${performance.now() - JStartTime}ms`);
		console.log('---------------------------------------');


		// WA实现
		var Module = {};
		var script = document.createElement('script');

		fetch('../out/fib.wasm').then(res => res.arrayBuffer()).then((bytes) => {
			Module.wasmBinary = bytes;
			script.src = '../out/fib.js';
			document.body.appendChild(script);
		});

		script.onload = function () {
			setTimeout(function () {
				let startTime = performance.now();
				console.log(Module["_fib"](45));
				console.log(`${performance.now() - startTime}ms`);
			}, 0);
		}
	</script>
</body>

</html>
