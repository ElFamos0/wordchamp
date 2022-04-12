<script setup>

// import des composants dont on a besoin

import Keyboard from '@/components/KeyBoard.vue';
import WordRow from '@/components/WordRow.vue';
import {onMounted, reactive} from "vue"
import axios from 'axios';

// path vers le backend

const path = `${process.env.VUE_APP_BACKEND_URL}/word`;

// gestion des inputs

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

/*
Variables "réactive qui va nou permettre de gèrer les données du jeu
*/

const game = reactive({
  solution: "",
  tried: ["", "", "", "", "", ""],
  currentTry: 0,
  solutionlength: 8,
})

// fonction pour vérifier qu'une entrée est une lettre

const isaLetter = (keypressed) => {
  return (keypressed.match(/[a-zA-Z]/) && keypressed.length == 1);
}

// fonction qui s'execute dès la création de la page 

onMounted(() => {
  window.addEventListener("keydown", (e) => {
    e.preventDefault();
    let key = e.keyCode == 13 ? '{enter}' 
    : e.keyCode == 8 ? '{bksp}' 
    : String.fromCharCode(e.keyCode).toUpperCase();
    displayinput(key);
    
  });
  // on récupère la solution depuis l'api
    axios.get(path)
        .then((res) => {
          game.solution = res.data;
        })
        .catch((error) => {
          // eslint-disable-next-line
          console.error(error);
        });
});

</script>


<template>
  <div class="random">
    <h1>Venez jouer à WordChamp</h1>
    <p>Voici la solution (en mode maxi tricherie): {{ game.solution }}</p>
    <!-- On utilise le composant wordrow avec toutes les props en arguments -->
    <word-row class="justify-center" v-for="(tryy,i) in game.tried" :key="i" :word="tryy" :submitted="i < game.currentTry"></word-row>
    <b-container>
      <!-- Clavier qui réagit avec l'action onKeyPress et active la fonction display input-->
      <Keyboard @onKeyPress="displayinput"></Keyboard>
    </b-container>
  </div>
</template>