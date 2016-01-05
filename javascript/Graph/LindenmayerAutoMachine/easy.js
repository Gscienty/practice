
var t = new turtle();

var re = new rewrite();

function b(str){
    re.setb(str);
}

function r(str){
    var arr = str.split('=');
    re.appendR(arr[0], arr[1]);
}

function c(){
    re.clr();
}

function d(i){
    var str = re.build(i);
    console.log(str);
    t.trans(str);
}

function a(i, j, k){
    t.setCam([i, j, k]);
}

function f(l){
    t.fovCam(l);
}

function l(i, j, k){
    t.loaCam([i, j, k]);
}
