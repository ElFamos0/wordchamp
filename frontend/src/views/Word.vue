<script setup>
import Keyboard from '@/components/KeyBoard.vue';
import {onMounted, ref} from "vue"

const displayinput = (keypressed) => {
  console.log(keypressed);
  if (isaLetter(keypressed)){
      text.value += keypressed;
      console.log(text.value);
  }

}

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
    <b-container>
      <Keyboard @onKeyPress="displayinput"></Keyboard>
    </b-container>
  </div>
</template>