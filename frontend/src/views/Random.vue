<template>
  <div class="random">
    <h1>Ceci est assez random</h1>
    <PingComponent />
  </div>
</template>

<script>
import PingComponent from '@/components/PingComponent.vue';

export default {
  name: 'random-page',
  components: {
    PingComponent,
  },
};
</script>
