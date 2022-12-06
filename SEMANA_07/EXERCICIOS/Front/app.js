const playerText = document.querySelector("#playerText");
const ComputadorText = document.querySelector("#ComputadorText");
const resultText = document.querySelector("#resultText");
const Botoes = document.querySelectorAll(".Botoes");

let player;
let Computador;
let result;

Botoes.forEach(button => button.addEventListener("click", () => {

    player = button.textContent;
    ComputadorTurn();

    playerText.textContent = "Player: " + player;
    ComputadorText.textContent = "Computador: " + Computador;
    resultText.textContent = checkWinner();

    result = checkWinner();
    console.log(result);
}));


function ComputadorTurn(){

    const Numaletorio = Math.floor(Math.random() * 3) + 1;

    switch(Numaletorio){
      case 1:
        Computador == "Pedra";
        break;
      case 2:
        Computador == "Papel";
        break;
      case 3:
        Computador == "Tesoura";
        break;
    }
}
function checkWinner(){
    if(player == Computador){
      return "Empate!";
    }
    else if(Computador == "Pedra" && player == "Tesoura"){
      return "Perdeu!";
    }
    else if(Computador == "Papel" && player == "Pedra"){
      return "Perdeu!";
    }
    else if(Computador == "Tesoura" && player == "Papel"){
      return  "Perdeu!";
    }  
    else if (player == "Pedra" && Computador == "Tesoura"){
      return "Ganhou!";
    }
    else if (player == "Papel" && Computador == "Pedra"){
      return "Ganhou!";
    }
    else if (player == "Tesoura" && Computador == "Papel"){
      return "Ganhou!";
    }
}

