<script setup>
import Keyboard from '@/components/KeyBoard.vue';
import WordRow from '@/components/WordRow.vue';
import {onMounted, reactive} from "vue"

const displayinput = (keypressed) => {
  if (game.currentTry >= 6) {
    return;
  }
  const wordguess = game.tried[game.currentTry];
  if (keypressed == "{enter}" && wordguess.length == game.solutionlength) {
    game.currentTry++;
  }
  if (keypressed == "{bksp}") {
    game.tried[game.currentTry] = wordguess.slice(0, -1);
  }
  if (isaLetter(keypressed) && wordguess.length < game.solutionlength) {
      game.tried[game.currentTry] += keypressed;
  }
  console.log(game.tried[game.currentTry]);
  }

const game = reactive({
  solution: "",
  tried: ["", "", "", "", "", ""],
  currentTry: 0,
  solutionlength: 8,
})


const isaLetter = (keypressed) => {
  return (keypressed.match(/[a-zA-Z]/) && keypressed.length == 1);
}

onMounted(() => {
  window.addEventListener("keydown", (e) => {
    e.preventDefault();
    let key = e.keyCode == 13 ? '{enter}' 
    : e.keyCode == 8 ? '{bksp}' 
    : String.fromCharCode(e.keyCode).toUpperCase();
    displayinput(key);
  });
});

</script>

<template>
  <div class="random">
    <h1>Venez jouer à WordChamp</h1>
    <p>Voici la valeur : {{ text }}</p>
    <word-row class="justify-center" v-for="(tryy,i) in game.tried" :key="i" :word="tryy" :submitted="i < game.currentTry"></word-row>
    <b-container>
      <Keyboard @onKeyPress="displayinput"></Keyboard>
    </b-container>
  </div>
</template>