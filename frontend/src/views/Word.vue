<script setup>
import Keyboard from '@/components/KeyBoard.vue';
import {onMounted} from "vue"

const displayinput = (keypressed) => {
  console.log(keypressed);
};

onMounted(() => {
  window.addEventListener("keypress", (e) => {
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
    <b-container>
      <Keyboard @onKeyPress="displayinput"></Keyboard>
    </b-container>
  </div>
</template>