(function(root){
    function rewrite(){
        var base = '';
        var rules = [];
        var ldep = 0.4;
        var rdep = 0.4;
        this.clr = function(){
            base = '';
            rules = [];
        }

        var lde = function(){
            return 1 - ldep * (1 - Math.random());
        }

        var rde = function(){
            return 1 - rdep * (1 - Math.random());
        }

        this.setb = function(b){
            base = b;
        }

        this.appendR = function(ru, gr){
            rules.push({
                ru: ru,
                gr: gr
            });
        };

        var equs = function(rs, b, bp){
            var rl = rs.length;
            var rp = 0;
            var bpp = 0;
            while(rp < rl){
                if(b[bp + bpp] === '('){
                    while(b[bp + bpp] != ')'){
                        bpp++;
                    }
                    bpp++;
                }

                if(b[bp + bpp] != rs[rp]){
                    return false;
                }

                bpp++;
                rp++;
            }

            return bpp;
        }

        var equ = function(b, p){
            var rlen = rules.length;
            for(var k = 0; k < rlen; k++){
                var equspr = equs(rules[k].ru, b, p);
                if(equspr != false){
                    return {
                        gr: rules[k].gr,
                        len: equspr
                    };
                }
            }
            return false;
        }

        var budgr = function(gr){
            var fg = 0x00;
            var grl = gr.length;
            var gp = 0;
            var rstr = '';
            while(gp < grl){
                if(gr[gp] === '"'){
                    fg = fg | 0x01;
                }
                else if(gr[gp] === ';'){
                    fg = fg | 0x02;
                }
                else{
                    if(gr[gp] === '('){
                        var ocmd = gr[gp - 1];
                        var num = '';
                        gp++;
                        while(gr[gp] != ')'){
                            num = num + gr[gp];
                            gp++;
                        }

                        if((fg & 0x01) != 0 && (ocmd === 'F' || ocmd === 'f' || gr[gp] === 'G')){
                            num = parseFloat(num) * lde();
                        }
                        if((fg & 0x02) != 0 && (ocmd === '-' || ocmd === '^' || ocmd === '/' || ocmd === '+' || ocmd === '&' || ocmd === '\\')){
                            num = parseFloat(num) * rde();
                        }
                        fg = 0x00;

                        rstr = rstr + '(' + num + ')';
                    }
                    else{
                        rstr = rstr + gr[gp];
                        if(fg != 0 && gr[gp + 1] != '('){
                            var num = 0;
                            if((fg & 0x01) != 0 && (gr[gp] === 'F' || gr[gp] === 'f' || gr[gp] === 'G')){
                                num = 1 * lde();
                            }
                            else if((fg & 0x02) != 0 && (gr[gp] === '-' || gr[gp] === '^' || gr[gp] === '/')){
                                num = 30 * rde();
                            }
                            else if((fg & 0x02) != 0 && (gr[gp] === '+' || gr[gp] === '&' || gr[gp] === '\\')){
                                num = 30 * rde();
                            }
                            rstr = rstr + '(' + num + ')';

                            fg = 0x00;
                        }
                    }
                }

                gp++;
            }

            return rstr;
        }

        this.build = function(step){
            var res = base;
            for(var i = 0; i < step; i++){
                var tres = '';
                var length = res.length;
                for(var j = 0; j < length; j++){
                    var equpr = equ(res, j);
                    if(equpr != false){
                        tres = tres + budgr(equpr.gr);
                        j = j + equpr.len - 1;
                    }
                    else{
                        tres = tres + res[j];
                    }
                }
                res = tres;
            }

            return res;
        }

    };

    root.rewrite = rewrite;

})(this);
