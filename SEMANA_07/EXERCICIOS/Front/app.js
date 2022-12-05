const playerText = document.querySelector("#playerText");
const ComputadorText = document.querySelector("#ComputadorText");
const resultText = document.querySelector("#resultText");
const choiceBtns = document.querySelectorAll(".choiceBtn");
let player;
let Computador;
let result;

choiceBtns.forEach(button => button.addEventListener("click", () => {

    player = button.textContent;
    ComputadorTurn();
    playerText.textContent = `Player: ${player}`;
    ComputadorText.textContent = `Computador: ${Computador}`;
    resultText.textContent = checkWinner();
}));

function ComputadorTurn(){

    const randNum = Math.floor(Math.random() * 3) + 1;

    switch(randNum){
      case 1:
        Computador = "Pedra";
        break;
      case 2:
        Computador = "Papel";
        break;
      case 3:
        Computador = "Tesoura";
        break;
    }
}
function checkWinner(){
    if(player == Computador){
      return "Empate!";
    }
    else if(Computador == "Pedra"){
      return (player == "Papel") ? "Ganhou!" : "Perdeu!"
    }
    else if(Computador == "Papel"){
      return (player == "Tesoura") ? "Ganhou!" : "Perdeu!"
    }
    else if(Computador == "Tesoura"){
      return (player == "Pedra") ? "Ganhou!" : "Perdeu!"
    }
}
