<template>
  <div class="random">
    <h1>Ceci est assez random</h1>
    <Ping />
  </div>
</template>

<script>
import Ping from '@/components/Ping.vue';

export default {
  name: 'Random',
  components: {
    Ping,
  },
};
</script>
