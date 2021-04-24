
let main = function main(){
    global.World = this
    this.start = function (){
        this.init('','','')
        document.getElementById('graphBtn').addEventListener('click',async ()=>{
            let v = Number(document.getElementById('v').value)
            let alpha = Number(document.getElementById('alpha').value)
            console.log({v,alpha})
            if( alpha=== 0 || alpha >=90 ){
                alert('not correct alpha')
                return false
            }
            let ball = this.world.ball
            let target = this.world.target
            let g = this.world.g
            let s = (target.x-ball.x)/10
            let h = (target.y-ball.y)/10
            let min = this.round(this.toDeg(this.alphaMin(h,s)))
            let a = {
                alpha,
                v,
                s:s,
                g:g
            }
            await this.traccert(a)
            await this.checkCompare()
            this.render()
        })
        document.getElementById('searchBtn').addEventListener('click',async ()=>{
            let v = Number(document.getElementById('v').value)
            console.log({v})
            await this.traccert(await this.search(v).then(el=>{
                alert('нашел угол: '+el.alpha)
                console.log(el)
                return el
            }))
            await this.checkCompare()
            this.render()
        })
    }
    this.search = function (v){
        return new Promise(async (resolve, reject) => {
            v = Number(v)
            if(v===0){
                alert('упал')
                reject()
            }
            if(v<0){
                alert('v must be > 0')
                reject()
            }
            let ball = this.world.ball
            let target = this.world.target
            let g = this.world.g
            let s = (target.x-ball.x)/10
            let h = (target.y-ball.y)/10
            let min = this.round(this.toDeg(this.alphaMin(h,s)))
            let t = ''
            let H = ''
            console.log({s,h,min,g})
            for(let i = min;i<90;i+=0.1){
                t = this.roundC(this.round(await this.calculateTime(s,i,v)))
                H = this.roundC(this.round(await this.calculateHeight(t,v,i,g)))
                console.log({i, t, H})
                if(H === h){
                    console.log({H})
                    resolve({alpha:i,s,h,v,g})
                    break
                }
            }
        })


    }
    this.traccert = async function (obj){
    //alpha, s, h,g
        let dataX = []
        let dataY = []
        let s = obj.s
        let alpha = obj.alpha
        let y = ''
        let t = ''
        for(let i = 0;i<=s;i+=0.1){
            t = this.roundC(this.round(this.calculateTime(i,alpha,obj.v)))
            y = this.roundC(this.round(await this.calculateHeight(t,obj.v,alpha,obj.g)))
            if(y<-2){
                break;
            }
            dataY.push(y+(this.world.ball.y/10))
            dataX.push(this.roundC(t))
            // dataX.push(this.roundB(i))
        }
        console.log({dataX,dataY})
        this.view.data.X = dataX
        this.view.data.Y = dataY
    }

    this.checkCompare = function(){
        let dataX = this.view.data.X
        let dataY = this.view.data.Y
        let tmpX = []
        let tmpY = []
        // console.log(dataX.length)
        if(dataX.length>1){
            for(let i = 0;i<dataX.length;i++){
                if(i===0){
                    tmpX.push(dataX[i])
                    tmpY.push(dataY[i])
                }
                if(dataY[i]===dataY[i-1]){

                }else{
                    tmpX.push(dataX[i])
                    tmpY.push(dataY[i])
                }
            }
            this.view.data.X = tmpX
            this.view.data.Y = tmpY
        }
    }

    this.view ={
        data:{}
    }

    this.render = function (data){
        let ctx = document.getElementById('myChart').getContext('2d')
        ctx.clearRect(0, 0, ctx.width, ctx.height)
        let chart = new Chart(ctx,{
            type:'line',
            data:{
                labels:data||this.view.data.X,
                datasets:[{
                    data:data || this.view.data.Y
                }]
            }
        })
    }

    this.init = function (ball, target, gravity){
        let world = {}
        world.ball = {
            x:ball.x || 0,
            y:ball.y || 20
        }
        world.target = {
            x:target.x || 100,
            y:target.y || 40
        }
        world.g = gravity || 9.8
        this.world = world
    }
    this.toRad = function (deg){
        return deg*Math.PI/180
    }
    this.toDeg = function (rad){
        return rad*180/Math.PI
    }
    this.calculateTime = function (S, alpha, v){
        return S/v*Math.cos(this.toRad(alpha))
    }
    this.calculateHeight = function (t, v, alpha, g){
        return v*t*Math.sin(this.toRad(alpha)) - (g*t*t)/2
    }
    this.alphaMin = function (h, s){
        return Math.atan2(h,s)
    }
    this.round = function (value){
        return Math.round(value*this.epsilon)/this.epsilon
    }
    this.roundB = function (value){
        return Math.round(value*this.epsilonB)/this.epsilonB
    }
    this.roundC = function (value){
        let a = Math.round(value*this.epsilonB)/this.epsilonB
        let b = value - a
        // console.log({value,a,b})
        b*=1000
        // console.log(b)
        b = Math.round(b)
        if(b>=85 || (b>=-15 && b<0)){
            return this.roundB(value)
        }else{
            return value
        }
    }
    this.epsilon = 100
    this.epsilonB = 10

}

module.exports = main
