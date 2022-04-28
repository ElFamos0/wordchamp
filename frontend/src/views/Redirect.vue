<script>
import axiosAuth from '@/api/axios-auth';

export default {
    data () {
      return {
          currentgamepath: `${process.env.VUE_APP_BACKEND_URL}/currentGame`,
          currentgame: false,
      }
    },
    name: 'redirect-page',
        mounted : function() {
        axiosAuth.get(this.currentgamepath).then((res) => {
        this.currentgame=res.data
        if (!this.currentgame) {
            console.log("je pars vers choice")
            this.$router.push('/choice')
        }
        else {
            console.log("je pars vers word")
            this.$router.push('/word/:5/:6')
        }
        })
    },

}

</script>
<template>
<div></div>
</template>

<style scoped>
</style>