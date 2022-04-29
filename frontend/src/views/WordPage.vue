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
          pathMotValide: `${process.env.VUE_APP_BACKEND_URL}/motValide`,
          dialog: false,
          gameShown: false,
          motValide : false,
          showError : false,
          game: {
            maxtry: 1,
            solution: "default",
            tried: ["","","","","",""],
            currentTry: 0,
            solutionlength: 8,
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
        //console.log("try avant ajout:", this.game.tried[this.game.currentTry])
        if (this.isaLetter(keypressed) && this.game.tried[this.game.currentTry].length < this.game.solutionlength) {
            this.game.tried[this.game.currentTry] += keypressed;
        }
        if (keypressed == "{enter}" && (this.game.tried[this.game.currentTry].length == this.game.solutionlength))
        { 
          const wordguess = this.game.tried[this.game.currentTry];
          this.motValide = this.verifTry(wordguess)
          //console.log("valeur de mot valide après la verifTry :", this.motValide)
          if (this.motValide) {
            // ici le mot est validé 
            this.motValide=false
            //console.log("j'ai remis à faux motValide :", this.motValide)
          for (var i = 0; i < wordguess.length; i++) {
            let c = wordguess.charAt(i);
            if (c == this.game.solution.charAt(i) && this.game.guessedletters.found.indexOf(c) == -1) {
              this.game.guessedletters.found.push(c);
            }
            else if (this.game.solution.indexOf(c) != -1 && this.game.guessedletters.misplace.indexOf(c) == -1) {
              this.game.guessedletters.misplace.push(c);
            } 
            else {
              if(this.game.guessedletters.miss.indexOf(c) == -1) {
                this.game.guessedletters.miss.push(c);
              }
            }
          
          }
          console.log("guessedletters:", this.game.guessedletters)
          this.game.currentTry++;
          axiosAuth.post(this.sendtry,{"data":wordguess})
            .then((res) => {
              this.showError = false;
              console.log("sendtry envoie à la DB :", wordguess, res)
            });
          } else {
            this.showError = false;
            window.setTimeout(() => { this.showError = true }, 0);
          }

          // handle de la coloration des touches du clavier
        }
        if (keypressed == "{bksp}") {
          this.game.tried[this.game.currentTry] = this.game.tried[this.game.currentTry].slice(0, -1);
        }
      },
      verifTry: function(wordguess) {
        //console.log("valeur de wordguess envoyé à veriTry :", wordguess)
        //console.log("motssss", this.game.motsValides)

        if (this.game.motsValides.includes(wordguess)) {
            this.motValide = true
        }
        console.log("valeur MAJ par verifTry : ", this.motValide)
        return this.motValide
      },
      isaLetter: function(keypressed) {
        return (keypressed.match(/[a-zA-Z]/) && keypressed.length == 1);
      },
      wincase: function() {
        if (this.game.tried[this.game.currentTry - 1] === this.game.solution){
          this.game.currentTry = 11;
          this.game.iswin = true;
        }
        return this.game.iswin
      },
      loosecase: function() {return (!this.wincase() && this.game.currentTry == this.game.maxtry)},
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
            console.log(res.data)
            this.game.solution = res.data.solution
            this.game.solutionlength = res.data.solution.length
            this.game.currentTry = res.data.currenttry
            this.game.tried = res.data.guess
            this.game.maxtry = res.data.maxtry
            this.game.motsValides = res.data.motsValides
            this.gameShown = true
            this.game.guessedletters.misplace = res.data.misplace
            this.game.guessedletters.miss = res.data.miss
            this.game.guessedletters.found = res.data.found
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
    <v-chip v-model="showError" class="text-center animatedChip mb-3" color="primary" dark height="200px" style="margin-top:1%">
      Ce mot n'est pas dans notre dictionnaire.
    </v-chip>
    <v-dialog v-model="this.dialog" persistent transition="dialog-top-transition">
      <v-card>
        <v-toolbar>Fin de partie</v-toolbar>
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
          <v-btn outlined raised rounded color="accent" @click="this.dialog = false; this.$confetti.stop(); this.$router.push('/')" >Maison</v-btn> 
          <v-btn outlined raised rounded color="accent" @click="this.dialog = false; this.$confetti.stop(); this.$router.push('/choice')" >Nouvelle partie</v-btn> 
        </v-card-actions>
      </v-card>
    </v-dialog>
    
    <div v-if="this.gameShown" style="margin-top:2%">
      <div v-for="(tryy,i) in this.game.tried" :key="i" >
        <word-row class="justify-center" :word="tryy" :size="this.game.tried.length" :submitted="i < this.game.currentTry" :solution="this.game.solution"></word-row>
      </div>
    </div>
    <b-container>
      <!-- Clavier qui réagit avec l'action onKeyPress et active la fonction display input-->
      <Keyboard style="color:#000" @onKeyPress="this.displayinput" :guessedletter=[]></Keyboard>
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