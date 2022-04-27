<script>

// import des composants dont on a besoin

import Keyboard from '@/components/KeyBoard.vue';
import WordRow from '@/components/WordRow.vue';
import axiosAuth from '@/api/axios-auth';
import {useRoute} from 'vue-router';

export default {
    name: 'word-page',
    components : {
        Keyboard,
        WordRow,
    },
    data() {
        return {
          creategame: `${process.env.VUE_APP_BACKEND_URL}/creategame`,
          sendtry: `${process.env.VUE_APP_BACKEND_URL}/send_try`,
          dialog: false,
          game: {
            solution: "default",
            tried: ["", "", "", "", "", ""],
            currentTry: 0,
            solutionlength: 8,
            iswin: false,
          },
        }
    },
    methods: {
      displayinput: function(keypressed) {
        if (this.game.currentTry >= 6) {
          return;
        }
        const wordguess = this.game.tried[this.game.currentTry];
        if (keypressed == "{enter}" && wordguess.length == this.game.solutionlength) {
          console.log("j'envoie la maxi sauce")
          this.game.currentTry++;
          axiosAuth.post(this.sendtry,{"data":wordguess})
            .then((res) => {
              console.log(res)
              });

          // handle de la coloration des touches du clavier
        }
        if (keypressed == "{bksp}") {
          this.game.tried[this.game.currentTry] = wordguess.slice(0, -1);
        }
        if (this.isaLetter(keypressed) && wordguess.length < this.game.solutionlength) {
            this.game.tried[this.game.currentTry] += keypressed;
        }
      },
      isaLetter: function(keypressed) {
        return (keypressed.match(/[a-zA-Z]/) && keypressed.length == 1);
      },
      wincase: function() {
        if (this.game.tried[this.game.currentTry - 1] === this.game.solution){
          this.game.currentTry = 10;
          this.game.iswin = true;
        }
        return this.game.iswin
      },
      loosecase: function() {return (!this.wincase() && this.game.currentTry == 6)},
      endcase: function() {return this.wincase() || this.loosecase()},
      handleKeys: function(e) {
        let key = e.keyCode == 13 ? '{enter}' 
        : e.keyCode == 8 ? '{bksp}' 
        : String.fromCharCode(e.keyCode).toUpperCase();
        this.displayinput(key);
        if (this.endcase()) {
          if (this.wincase()) {
            this.$confetti.start();
          }
          this.dialog = true;
        }
      },
    },
    mounted() {
      window.addEventListener("keydown", this.handleKeys);
      // on récupère la solution depuis l'api on récupère une taille de mot en particulier si pas de taille renseigné on choisit une taille aléatoire.
      const route = useRoute()
      const id = route.params.i
      const id2 = id.slice(1,2)
      console.log(id2)
        axiosAuth.get(this.creategame+"/"+id2)
            .then((res) => {
              console.log(res.data)
              this.game.solution = res.data.solution
              this.game.solutionlength = res.data.solution.length
              this.game.currentTry = res.data.currenttry
              this.game.tried = res.data.guess
            });
    },
    unmounted() {
      window.removeEventListener("keydown", this.handleKeys);
    }
}
</script>

<template>
  <div class="random">
    <h1 style="margin-bottom:1%">Venez jouer à WordChamp</h1>
    <!-- On utilise le composant wordrow avec toutes les props en arguments -->
    <v-dialog v-model="this.dialog" persistent transition="dialog-top-transition">
      <v-card>
        <v-toolbar>Oof</v-toolbar>
        <v-card-text>
          <div v-if="this.loosecase()">
            <p>
              Vous avez perdu !
            </p>
            <p>
              La solution était {{this.game.solution}}
            </p>
          </div>
          <div v-if="this.wincase()">
            <p>
              Vous avez gagné !
            </p>
          </div>
        </v-card-text>
        <v-card-actions class="justify-end">
          <v-btn text @click="this.$confetti.stop(); this.$router.go('/')" >Nouvelle partie</v-btn> 
        </v-card-actions>
      </v-card>
    </v-dialog>
    <word-row class="justify-center" v-for="(tryy,i) in this.game.tried" :key="i" :word="tryy" :submitted="i < this.game.currentTry" :solution=this.game.solution></word-row>

    <b-container>
      <!-- Clavier qui réagit avec l'action onKeyPress et active la fonction display input-->
      <Keyboard style="color:#000" @onKeyPress="this.displayinput"></Keyboard>
    </b-container>
  </div>
</template>