//point
(function(root){
	function Point(x, y){
		this.X = x;
		this.Y = y;
	}
	
	root.Point = Point;
	root.ctorPoint = function(x, y){
		return new Point(x, y);
	}
})(this);

//line
(function(root){
	function line(p1, p2){
		this.p1 = p1;
		this.p2 = p2;
	};
	
	root.Line = line;
})(this);

//arrangement
(function(root){
	function arrangement(){
		var lines = [];
		
		this.append = function(line){
			lines.push(line);
			return this;
		};
		
		var drawProcedure = function(trans, ctx, loop){
			if(loop === 0) return;
			ctx.save();
			trans(ctx, loop);
			lines.forEach(function(value){
				ctx.beginPath();
				ctx.moveTo(value.p1.X, value.p1.Y);
				ctx.lineTo(value.p2.X, value.p2.Y);
				ctx.closePath();
				ctx.stroke();
			});
			ctx.restore();
			
			drawProcedure(trans, ctx, loop-1);
			
		}
		
		this.display = function(name, loop, trans){
			var cvs = document.getElementById(name);
			var ctx = cvs.getContext('2d');
			ctx.fillStyle = '#000';
			drawProcedure(trans, ctx, loop);
			return this;
		}
		
		this.transf = function(name, func){
			func(document.getElementById(name).getContext('2d'));
			return this;
		}
		
		this.save = function(name){
			document.getElementById(name).getContext('2d').save();
		}
		
		this.reset = function(name){
			document.getElementById(name).getContext('2d').restore();
		}
	};
	
	root.Arrangement = arrangement;
})(this);