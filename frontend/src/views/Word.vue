<script setup>
import Keyboard from '@/components/KeyBoard.vue';
import {onMounted} from "vue"

const displayinput = (keypressed) => {
  console.log(keypressed);
};

onMounted(() => {
  window.addEventListener("keypress", (e) => {
    console.log(e.key);
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