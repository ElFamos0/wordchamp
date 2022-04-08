<script setup>
import Keyboard from '@/components/KeyBoard.vue';
import WordRow from '@/components/WordRow.vue';
import {onMounted, reactive, ref} from "vue"

const displayinput = (keypressed) => {
  console.log(keypressed);
  if (isaLetter(keypressed)){
      text.value += keypressed;
      console.log(text.value);
  }

}

const etat = reactive({
  solution: "",
  try: ["", "", "", "", "", ""],
  currentTry: 0,
})

console.log(etat.try);


const isaLetter = (keypressed) => {
  return (keypressed.match(/[a-zA-Z]/) && keypressed.length == 1);
}

const text = ref("")


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
    <word-row class="justify-center" v-for="i in 6" :key="i" ></word-row>
    <b-container>
      <Keyboard @onKeyPress="displayinput"></Keyboard>
    </b-container>
  </div>
</template>