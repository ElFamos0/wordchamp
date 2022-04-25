<script setup>

// import des composants dont on a besoin

import Keyboard from '@/components/KeyBoard.vue';
import WordRow from '@/components/WordRow.vue';
import {onMounted, onUnmounted, reactive} from "vue"
import axiosAuth from '@/api/axios-auth';
import { useRoute } from 'vue-router'




// path vers le backend


const creategame = `${process.env.VUE_APP_BACKEND_URL}/creategame`;
const sendtry = `${process.env.VUE_APP_BACKEND_URL}/send_try`;
// gestion des inputs

const displayinput = (keypressed) => {
  if (game.currentTry >= 6) {
    return;
  }
  const wordguess = game.tried[game.currentTry];
  if (keypressed == "{enter}" && wordguess.length == game.solutionlength) {
    console.log("j'envoie la maxi sauce")
    game.currentTry++;
    axiosAuth.post(sendtry,{"data":wordguess})
      .then((res) => {
        console.log(res)
        });

    // handle de la coloration des touches du clavier
  }
  if (keypressed == "{bksp}") {
    game.tried[game.currentTry] = wordguess.slice(0, -1);
  }
  if (isaLetter(keypressed) && wordguess.length < game.solutionlength) {
      game.tried[game.currentTry] += keypressed;
  }
}

/*
Variables "réactive qui va nou permettre de gèrer les données du jeu
*/

const game = reactive({
  solution: "default",
  tried: ["", "", "", "", "", ""],
  currentTry: 0,
  solutionlength: 8,
  iswin: false,
})

// fonction pour vérifier qu'une entrée est une lettre

const isaLetter = (keypressed) => {
  return (keypressed.match(/[a-zA-Z]/) && keypressed.length == 1);
}

// on regarde si la dernière entrée est bonne

const wincase = () => {
  if (game.tried[game.currentTry - 1] === game.solution){
    game.currentTry = 10;
    game.iswin = true;
  }
  return game.iswin
  }

// on vérifie qu"on a pas gagné et qu'on a fait tout les essais qui nous sont autorisés 

const loosecase = () => {return (!wincase() && game.currentTry == 6)}


// fonction qui s'execute dès la création de la page 
function handleKeys(e) {
    let key = e.keyCode == 13 ? '{enter}' 
    : e.keyCode == 8 ? '{bksp}' 
    : String.fromCharCode(e.keyCode).toUpperCase();
    displayinput(key);
    
}

onMounted(() => {
  window.addEventListener("keydown", handleKeys);
  // on récupère la solution depuis l'api on récupère une taille de mot en particulier si pas de taille renseigné on choisit une taille aléatoire.
  const route = useRoute()
  const id = route.params.i
  const id2 = id.slice(1,2)
  console.log(id2)
    axiosAuth.get(creategame+"/"+id2)
        .then((res) => {
          console.log(res.data)
          game.solution = res.data.solution
          game.solutionlength = res.data.solution.length
          game.currentTry = res.data.currenttry
          game.tried = res.data.guess
        });
});

onUnmounted(() => {
  window.removeEventListener("keydown", handleKeys)
})

</script>


<template>
  <div class="random">
    <h1 style="margin-bottom:1%">Venez jouer à WordChamp</h1>
    <!-- On utilise le composant wordrow avec toutes les props en arguments -->
    <word-row class="justify-center" v-for="(tryy,i) in game.tried" :key="i" :word="tryy" :submitted="i < game.currentTry" :solution=game.solution></word-row>
    <p v-if="loosecase()" class="text-center">Vous avez perdu le mot est {{game.solution}}</p>
    <p v-if="wincase()" style="text-align:center" >Vous avez gagné</p>
    <b-container>
      <!-- Clavier qui réagit avec l'action onKeyPress et active la fonction display input-->
      <Keyboard @onKeyPress="displayinput"></Keyboard>
    </b-container>
  </div>
</template>