<template>
  <div class="random">
    <h1>Venez jouer à WordChamp</h1>
    <GetWord />
    <Keyboard />
  </div>
</template>

<script>

import GetWord from '@/components/GetWord.vue';
import Keyboard from '../components/Keyboard.vue';

export default {
  name: 'Word',
  components: {
    GetWord,
    Keyboard,
  },
};
</script>
