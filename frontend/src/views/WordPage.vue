<script>

// import des composants dont on a besoin

import Keyboard from '@/components/KeyBoard.vue';
import WordRow from '@/components/WordRow.vue';
import axiosAuth from '@/api/axios-auth';
import {useRoute} from 'vue-router'; 
import LoadingSlider from '../components/LoadingSlider.vue';

export default {
    name: 'word-page',
    components : {
        Keyboard,
        WordRow,
        LoadingSlider,
    },
    data() {
        return {
          creategame: `${process.env.VUE_APP_BACKEND_URL}/creategame`,
          sendtry: `${process.env.VUE_APP_BACKEND_URL}/send_try`,
          pathMotValide: `${process.env.VUE_APP_BACKEND_URL}/motValide`,
          dialog: false,
          gameShown: false,
          motValide : false,
          showError : false,
          game: {
            maxtry: 1,
            solutionLength: 5,
            tried: ["","","","","",""],
            colors: [[],[],[],[],[],[]],
            currentTry: 0,
            iswin: false,
            motsValides: [],
            guessedletters: {
              miss: [],
              found: [],
              misplace: [],
            }
          },
        }
    },
    methods: {
      displayinput: function(keypressed) {
        if (this.game.currentTry >= this.game.maxtry) {
          return;
        }
        //// console.log("try avant ajout:", this.game.tried[this.game.currentTry])
        if (this.isaLetter(keypressed) && this.game.guess[this.game.currentTry].length < this.game.solution) {
            this.game.guess[this.game.currentTry] += keypressed;
        }
        if (keypressed == "{enter}" && (this.game.guess[this.game.currentTry].length == this.game.solution))
        { 
          const wordguess = this.game.guess[this.game.currentTry];
          this.motValide = this.verifTry(wordguess)
          //// console.log("valeur de mot valide après la verifTry :", this.motValide)
          if (this.motValide) {
            // ici le mot est validé 
            this.motValide=false
            //// console.log("j'ai remis à faux motValide :", this.motValide)
          
          // console.log("guessedletters:", this.game.guessedletters)
          axiosAuth.post(this.sendtry,{"data":wordguess})
            .then((resp) => {
              this.showError = false;
              this.game.colors[this.game.currentTry] = resp.data.colors
              this.game.currentTry++;
              this.game.guessedletters = resp.data.guessedletters

              if(resp.data.ended) {
                if (resp.data.victory) {
                  this.game.currentTry = 11;
                  this.game.iswin = true;
                } else {
                  this.game.answer = resp.data.solution
                  this.game.iswin = false;
                }
                this.handleKeys(keypressed)
              }

              console.log(this.game.solution)
            });
          } else {
            this.showError = false;
            window.setTimeout(() => { this.showError = true }, 0);
          }

          // handle de la coloration des touches du clavier
        }
        if (keypressed == "{bksp}") {
          this.game.guess[this.game.currentTry] = this.game.guess[this.game.currentTry].slice(0, -1);
        }
      },
      verifTry: function(wordguess) {
        //// console.log("valeur de wordguess envoyé à veriTry :", wordguess)
        //// console.log("motssss", this.game.motsValides)

        if (this.game.motsValides.includes(wordguess)) {
            this.motValide = true
        }
        // console.log("valeur MAJ par verifTry : ", this.motValide)
        return this.motValide
      },
      isaLetter: function(keypressed) {
        return (keypressed.match(/[a-zA-Z]/) && keypressed.length == 1);
      },
      wincase: function() {
        return this.game.iswin
      },
      loosecase: function() {return (!this.wincase() && this.game.currentTry == this.game.maxtry)},
      endcase: function() {return this.wincase() || this.loosecase()},
      handleKeys: function(e) {
        let key = e.keyCode == 13 ? '{enter}' 
        : e.keyCode == 8 ? '{bksp}' 
        : String.fromCharCode(e.keyCode).toUpperCase();
        if (key == '{enter}' || key == '{bksp}') {
          e.preventDefault();
        }
        this.displayinput(key);
        if (this.endcase()) {
          if (this.wincase()) {
            this.$confetti.start();
          }
          this.dialog = true;
        }
      },
      hideError() {
        this.showError=false;
      }
    },
    mounted() {
      window.addEventListener("keydown", this.handleKeys);
      // on récupère la solution depuis l'api on récupère une taille de mot en particulier si pas de taille renseigné on choisit une taille aléatoire.
      const route = useRoute()  
      const id = route.params.i
      const id2 = id.slice(1,2)
      const id3 = route.params.j
      const id4 = id3.slice(1,3)
      axiosAuth.get(this.creategame+"/"+id2+"/"+id4)
          .then((res) => {
            for (const property in res.data) {
              this.game[property] = res.data[property]
            }
            this.gameShown = true
          });
      
    },
    unmounted() {
      window.removeEventListener("keydown", this.handleKeys);
      this.dialog = false;
      this.$confetti.stop();
    }
}
</script>

<template>
  <div class="random">
    <!-- On utilise le composant wordrow avec toutes les props en arguments -->
    <h1 class="mt-3">Mode classique</h1>
    <v-chip v-model="showError" class="text-center animatedChip mt-5" color="primary" dark height="200px" style="margin-top:1%;font-family: 'Roboto', sans-serif">
      Ce mot n'est pas dans notre dictionnaire.
    </v-chip>
    <v-dialog v-model="this.dialog" persistent transition="dialog-top-transition">
      <v-card>
        <v-toolbar>Fin de partie</v-toolbar>
        <v-card-text>
          <div v-if="this.loosecase()">
            <p style="font-family: 'Roboto', sans-serif">
              Vous avez perdu !
            </p>
            <p style="font-family: 'Roboto', sans-serif">
              La solution était {{this.game.answer}}
            </p>
          </div>
          <div v-if="this.wincase()">
            <p style="font-family: 'Roboto', sans-serif">
              Vous avez gagné !
            </p>
          </div>
        </v-card-text>
        <v-card-actions class="justify-end">
          <v-btn outlined raised rounded color="accent" @click="this.dialog = false; this.$confetti.stop(); this.$router.push('/')" style="font-family: 'Roboto', sans-serif" >Maison</v-btn> 
          <v-btn outlined raised rounded color="accent" @click="this.dialog = false; this.$confetti.stop(); this.$router.push('/choice')" style="font-family: 'Roboto', sans-serif" >Nouvelle partie</v-btn> 
        </v-card-actions>
      </v-card>
    </v-dialog>
    
    <loading-slider class="m-5" v-if="!this.gameShown"/>
    <div v-if="this.gameShown" class="mt-5">
      <div v-for="(tryy,i) in this.game.guess" :key="i" >
        <word-row class="justify-center" :word="tryy" :size="this.game.solution" :submitted="i < this.game.currentTry" :colors="this.game.colors[i]"></word-row>
      </div>
    </div>
    <b-container>
      <!-- Clavier qui réagit avec l'action onKeyPress et active la fonction display input-->
      <Keyboard style="color:#000" @onKeyPress="this.displayinput" :guessedletter="this.game.guessedletters"></Keyboard>
    </b-container>
  </div>
</template>

<style scoped>
.v-btn {
  background-color:rgb(201, 72, 255);
}

.animatedChip {
  animation: shake 0.82s cubic-bezier(.36,.07,.19,.97) both;
  animation-fill-mode: forwards;
}

@keyframes shake {
  10%, 90% {
    transform: translate3d(-2px, 0, 0);
  }
  
  20%, 80% {
    transform: translate3d(4px, 0, 0);
  }

  30%, 50%, 70% {
    transform: translate3d(-8px, 0, 0);
  }

  40%, 60% {
    transform: translate3d(8px, 0, 0);
  }
}
</style>