(function(root){
    function turtle(){
        var scene;
        var camera;
        var renderer;

        var render;

        var tp = [];
        var th = [];
        var tr = [];
        var remember = [];


        this.reset = function(){
            tp = [0, 0, 0];
            th = [0, 1, 0];
            tr = [0, 0, 90];
            remember = [];
        };

        //ctor
        (function(root){
            scene = new THREE.Scene();
            camera = new THREE.PerspectiveCamera(105, window.innerWidth / window.innerHeight, 0.1, 1000);
            renderer = new THREE.WebGLRenderer();
            renderer.setSize(window.innerWidth, window.innerHeight);
            document.body.appendChild(renderer.domElement);

            root.reset();

            camera.position.z = 15;

            render = function(){
                renderer.render(scene, camera);
            };
        })(this);

        this.setCam = function(pos){
            camera.position.x = pos[0];
            camera.position.y = pos[1];
            camera.position.z = pos[2];
            camera.lookAt(scene.position);
            render();
        }

        this.loaCam = function(pos){
            camera.lookAt(new THREE.Vector3(pos[0], pos[1], pos[2]));
            render();
        };

        this.fovCam = function(fv){
            camera.fov = fv;
            camera.updateProjectionMatrix();
            render();
        }

        this.go = function(distance, color, width){
            if(color === undefined){
                color = 0xffffff;
            }
            if(width === undefined){
                width = 1;
            }
            var material = new THREE.LineBasicMaterial({ color : color, 'linewidth': width});
            var geometry = new THREE.Geometry();

            geometry.vertices.push(
                new THREE.Vector3(tp[0], tp[1], tp[2]),
                new THREE.Vector3(tp[0] + th[0]*distance, tp[1] + th[1]*distance, tp[2] + th[2]*distance)
            );

            this.jmp(distance);

            scene.add(new THREE.Line(geometry, material));
        }

        this.jmp = function(distance){
            for(var i = 0; i < 3; i++){
                tp[i] = tp[i] + th[i]*distance;
            }
        }

        this.rok = function(angle){
            tr[2] = (tr[2] + angle) % 360;
            var l = Math.sqrt(th[0] * th[0] + th[1] * th[1]);
            th[0] = l * Math.cos(2 * Math.PI / 360 * tr[2]);
            th[1] = l * Math.sin(2 * Math.PI / 360 * tr[2]);
        }

        this.roi = function(angle){
            tr[0] = (tr[0] + angle) % 360;
            var l = Math.sqrt(th[1] * th[1] + th[2] * th[2]);
            th[1] = l * Math.cos(2 * Math.PI / 360 * tr[0]);
            th[2] = l * Math.sin(2 * Math.PI / 360 * tr[0]);
        }

        this.roj = function(angle){
            tr[1] = (tr[1] + angle) % 360;
            var l = Math.sqrt(th[0] * th[0] + th[2] * th[2]);
            th[2] = l * Math.cos(2 * Math.PI / 360 * tr[1]);
            th[0] = l * Math.sin(2 * Math.PI / 360 * tr[1]);
        }

        this.rem = function(){
            var r_tp = [];
            var r_th = [];
            var r_tr = [];
            for(var i = 0; i < 3; i++){
                r_tp.push(tp[i]);
                r_th.push(th[i]);
                r_tr.push(tr[i]);
            }

            remember.push({
                tp: r_tp,
                th: r_th,
                tr: r_tr
            });
        }

        this.rec = function(){
            var r = remember.pop();
            for(var i = 0; i < 3; i++){
                tp[i] = r.tp[i];
                th[i] = r.th[i];
                tr[i] = r.tr[i];
            }
        }


        var getcmd = function(str, p, l){
            var result = {};
            result.cmd = str[p];
            if(p+1 != l && str[p+1] === '('){
                p = p + 2;
                var temp = '';
                while(str[p] != ')' && p < l){
                    temp = temp + str[p];
                    p = p + 1;
                }
                result.param = parseFloat(temp);
                result.jmp = p;
            }
            else{
                result.param = 'default';
                result.jmp = p + 1;
            }
            return result;
        }

        this.trans = function(str){
            var length = str.length;
            var p = 0;

            while(p < length){
                //need like "regex" auto machine
                var cmds = getcmd(str, p, length);
                p = cmds.jmp;

                switch(cmds.cmd){
                    case 'F':
                        if(cmds.param === 'default'){
                            this.go(1, 0x99FFCC);
                        }
                        else{
                            this.go(cmds.param, 0x99FFCC);
                        }
                    break;

                    case 'G':
                        if(cmds.param === 'default'){
                            this.go(1, 0x00FF66);
                        }
                        else{
                            this.go(cmds.param, 0x00FF66);
                        }
                    break;

                    case 'f':
                        if(cmds.param === 'default'){
                            this.jmp(1);
                        }
                        else{
                            this.jmp(cmds.param);
                        }
                    break;

                    case '[':
                        this.rem();
                    break;

                    case ']':
                        this.rec();
                    break;

                    case '-':
                        if(cmds.param === 'default'){
                            this.rok(30);
                        }
                        else{
                            this.rok(cmds.param);
                        }
                    break;

                    case '+':
                        if(cmds.param === 'default'){
                            this.rok(-30);
                        }
                        else{
                            this.rok(-cmds.param);
                        }
                    break;

                    case '^':
                        if(cmds.param === 'default'){
                            this.roi(30);
                        }
                        else{
                            this.roi(cmds.param);
                        }
                    break;

                    case '&':
                        if(cmds.param === 'default'){
                            this.roi(-30);
                        }
                        else{
                            this.roi(-cmds.param);
                        }
                    break;

                    case '/':
                        if(cmds.param === 'default'){
                            this.roj(30);
                        }
                        else{
                            this.roj(cmds.param);
                        }
                    break;

                    case '\\':
                        if(cmds.param === 'default'){
                            this.roj(-30);
                        }
                        else{
                            this.roj(-cmds.param);
                        }
                    break;
                }

                render();
            }
        }
    };

    root.turtle = turtle;
})(this);
